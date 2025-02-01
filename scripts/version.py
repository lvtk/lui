#!/usr/bin/env python
# encoding: utf-8
# Michael Fisher, 2022
# Copyright 2022 Michael Fisher <mfisher@lvtk.org>
# SPDX-License-Identifier: ISC

from optparse import OptionParser
from subprocess import call, Popen, PIPE
import os

VERSION="3.0.0"
LAST_VERSION="0d12d1ecbc5a32db1475bf20ca621ec038d0e4de"

def options():
    parser = OptionParser()
    parser.add_option ("--before", type="string", dest="before", default='')
    parser.add_option ("--after", type="string", dest="after", default='')
    parser.add_option ("--last-version", type="string", dest="last_version", default=LAST_VERSION)
    parser.add_option ("--revision", action="store_true", dest="revision", default=False)
    parser.add_option ("--build", action="store_true", dest="build", default=False)
    parser.add_option ("--no-version", action="store_true", dest="no_version", default=False)
    parser.add_option ("--cwd", type="string", dest="cwd", default='')
    parser.add_option ("--ignore-dirty", action="store_true", dest="ignore_dirty", default=False)
    (opts, _) = parser.parse_args()
    return opts

def call_git (ctx, args):
    if not os.path.exists('.git'):
        return (False, 'Not a git repository')
    cmd = ['git'] if ctx == None else [] + ctx.env.GIT
    if not isinstance (cmd, list): return False
    if not isinstance (args, list): args = []
    devnull = open (os.devnull, 'w')
    cmd += args
    P = Popen (cmd, stdout=PIPE, stderr=devnull)
    (r, err) = P.communicate()
    P.wait()
    return (r, err)

def exists():
    '''Returns true if the current directory is a git repository'''
    return os.path.exists ('.git')

def ncommits (revision):
    args = 'rev-list %s..HEAD' % revision
    (n, err) = call_git (None, args.split())
    if None == err:
        return len (n.split())
    return 0

def nchanges():
    if not exists(): return 0
    (out, err) = call_git (None, 'status --porcelain --untracked-files=no'.split())
    if isinstance (out, str):
        return len(out.splitlines())

    return 0

def is_dirty():
    return nchanges() > 0

def get_hash (what='HEAD'):
    if not exists(): return ''
    args = 'rev-parse %s' % what
    (r, e) = call_git (None, args.strip().split())
    return r.strip()

def get_hash_short (what='HEAD'):
    if not exists(): return ''
    args = 'rev-parse --short %s' % what
    (r, e) = call_git (None, args.strip().split())
    return r.strip()

def version():
    here = os.getcwd()
    opts = options()
    if len(opts.cwd) > 0:
        os.chdir (opts.cwd)

    vers = ''
    if not opts.no_version:
        vers = VERSION

    if exists():
        if opts.build:
            if opts.no_version:
                vers = '%s' % ncommits (opts.last_version)
            else:
                vers += '.%s' % ncommits (opts.last_version)
        elif opts.revision:
            if opts.no_version:
                vers = 'r%s' % ncommits (opts.last_version)
            else:
                vers += '_r%s' % ncommits (opts.last_version)

        if is_dirty() and not opts.ignore_dirty:
            vers += "-dirty"

    os.chdir (here)
    print ('%s%s%s' % (opts.before, vers, opts.after))
    return 0

if __name__ == '__main__':
    exit (version())
