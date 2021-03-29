#include "CustomSource_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

CustomSource_base::CustomSource_base(const char *uuid, const char *label) :
    Component(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    dataOctet_out = new bulkio::OutOctetPort("dataOctet_out");
    addPort("dataOctet_out", dataOctet_out);
    dataChar_out = new bulkio::OutCharPort("dataChar_out");
    addPort("dataChar_out", dataChar_out);
    dataShort_out = new bulkio::OutShortPort("dataShort_out");
    addPort("dataShort_out", dataShort_out);
    dataUshort_out = new bulkio::OutUShortPort("dataUshort_out");
    addPort("dataUshort_out", dataUshort_out);
    dataUlong_out = new bulkio::OutULongPort("dataUlong_out");
    addPort("dataUlong_out", dataUlong_out);
    dataLong_out = new bulkio::OutLongPort("dataLong_out");
    addPort("dataLong_out", dataLong_out);
    dataFloat_out = new bulkio::OutFloatPort("dataFloat_out");
    addPort("dataFloat_out", dataFloat_out);
    dataDouble_out = new bulkio::OutDoublePort("dataDouble_out");
    addPort("dataDouble_out", dataDouble_out);
}

CustomSource_base::~CustomSource_base()
{
    delete dataOctet_out;
    dataOctet_out = 0;
    delete dataChar_out;
    dataChar_out = 0;
    delete dataShort_out;
    dataShort_out = 0;
    delete dataUshort_out;
    dataUshort_out = 0;
    delete dataUlong_out;
    dataUlong_out = 0;
    delete dataLong_out;
    dataLong_out = 0;
    delete dataFloat_out;
    dataFloat_out = 0;
    delete dataDouble_out;
    dataDouble_out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void CustomSource_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Component::start();
    ThreadedComponent::startThread();
}

void CustomSource_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Component::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void CustomSource_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Component::releaseObject();
}

void CustomSource_base::loadProperties()
{
    addProperty(connection_type,
                "server",
                "connection_type",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(ip_address,
                "ip_address",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(port,
                "port",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(status,
                "status",
                "",
                "readonly",
                "",
                "external",
                "configure");

    addProperty(total_bytes,
                "total_bytes",
                "",
                "readonly",
                "",
                "external",
                "configure");

    addProperty(bytes_per_sec,
                "bytes_per_sec",
                "",
                "readonly",
                "",
                "external",
                "configure");

    addProperty(max_bytes,
                16384,
                "max_bytes",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(min_bytes,
                16384,
                "min_bytes",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(byte_swap,
                0,
                "byte_swap",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(internal_buffer_size,
                64,
                "internal_buffer_size",
                "internal_buffer_size",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(socket_settings,
                socket_settings_struct(),
                "socket_settings",
                "socket_settings",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(sri,
                sri_struct(),
                "sri",
                "",
                "readwrite",
                "",
                "external",
                "configure");

}


