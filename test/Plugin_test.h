#ifndef FDCORE_PLUGIN_TEST_H
#define FDCORE_PLUGIN_TEST_H

#include "test_PluginApi.h"

#include <FDCore/PluginManagement/Plugin.h>

TEST(Plugin_test, test_loading)
{
    FDCore::Plugin<FDCore::PluginApi> plugin("test_plugin", "FDCore_test_plugin");
    FDCore::AbstractPlugin::ApiEntryPoint entryPoint;
    entryPoint.type = FDCore::AbstractPlugin::Variable;
    entryPoint.symbolName = "plugin";
    std::any entryPointAny = &entryPoint;
    plugin.load(entryPointAny);
    ASSERT_TRUE(plugin.isLoaded());
    EXPECT_EQ(plugin->i, 42);
    EXPECT_NEAR(plugin->pi, 3.14159f, 0.00001f);
    EXPECT_TRUE(plugin->b);
    EXPECT_EQ(plugin->c, 'c');

    FAIL() << R"(Googletest code seems unable to load the plugin correctly.
    It might be caused by the instantiation of the plugin global variable
    that is not done yet at the moment the code is executed)";
        EXPECT_EQ(plugin->str, "string");

        EXPECT_EQ(plugin->f_i(), 1);
        EXPECT_NEAR(plugin->f_f(), 3.14159f / 3, 0.00001f);
        EXPECT_FALSE(plugin->f_b());
        EXPECT_EQ(plugin->f_c(), 'd');
        EXPECT_EQ(plugin->f_str(), "f_string result");

    plugin.release();
}

#endif // FDCORE_PLUGIN_TEST_H