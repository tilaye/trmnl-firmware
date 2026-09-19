#pragma once

#include <Arduino.h>
#include <WiFiGeneric.h>
#include <WiFiType.h>
#include <WiFi.h>

struct WifiCredentials
{
    String ssid;
    String pswd;
    // WPA2 Enterprise fields
    bool isEnterprise = false;
    String username;
    String identity;
    // Static IP fields (optional - leave empty for DHCP)
    bool useStaticIP = false;
    String staticIP;    // e.g., "192.168.1.100"
    String gateway;     // e.g., "192.168.1.1" (optional - defaults to x.x.x.1)
    String subnet;      // e.g., "255.255.255.0" (optional - defaults to 255.255.255.0)
    String dns1;        // optional - defaults to gateway
    String dns2;        // optional - defaults to 8.8.8.8
};

struct Network
{
    String ssid;
    int32_t rssi;
    bool open;
    bool saved;
    bool enterprise;
};

struct WifiEventData
{
    bool disconnected = false;
    wifi_err_reason_t disconnectReason = wifi_err_reason_t::WIFI_REASON_UNSPECIFIED;
    int eventCount = 0;
};

struct WifiConnectionResult
{
    wl_status_t status;
    WifiEventData eventData;
};

// The portal's address. The AP takes it (WifiCaptive.cpp), the redirects
// point at it (WebServer.h LocalIPURL) and the setup screen prints it
// (display.cpp), so none of them can disagree. It is printed because the
// captive popup does not always come, and a phone that types it must use
// http:// — unit #2's first setup (2026-09-18) went nowhere over https.
#define WIFI_PORTAL_IP 10, 254, 0, 1
#define WIFI_PORTAL_URL "http://10.254.0.1"
