################
Dynamic Manifest
################

`Dynamic Manifest <https://lv2plug.in/ns/ext/dynmanifest>`__ support.  This 
is a simple interface that implements dynmanifest boiler plate code in an easy
to use C++ class & factory function.  See the example below.

.. code-block:: cpp

   #include <lui/dynmanifest.hpp>

**Spec:** `<https://lv2plug.in/ns/ext/dynmanifest>`__

-------
Example
-------

.. code-block:: cpp

    #include <lui/dynmanifest.hpp>

    class MyManifest : public lui::DynManifest {
    public:
        bool get_subjects (std::stringstream& lines) override {
            lines << "@prefix doap:  <http://usefulinc.com/ns/doap#> . " << std::endl
                    << "@prefix lv2:   <http://lv2plug.in/ns/lv2core#> . " << std::endl
                    << "<http://myplugin.org> a lv2:Plugin ;" << std::endl;
            return true;
        }

        bool get_data (std::stringstream& lines, const std::string& uri) override {
            lines << "doap:name \"My Plugin\" ;" << std::endl;
            return true;
        }
    };

    // Required factory function.
    // used by dynmanifest.hpp to create your instance. Everything else
    // is handled internally.  This function can (and should) have hidden
    // visibility.
    void* lui_create_dyn_manifest() {
        return new MyManifest();
    }