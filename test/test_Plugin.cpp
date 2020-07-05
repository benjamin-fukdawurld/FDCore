#include "test_Plugin.h"

int FDCore::Plugin::f_i() { return 1; }
float FDCore::Plugin::f_f() { return pi / 3; }
bool FDCore::Plugin::f_b() { return false; }
char FDCore::Plugin::f_c() { return 'd'; }
std::string FDCore::Plugin::f_str() { return "f_string result"; }