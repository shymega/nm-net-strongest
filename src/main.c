#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

NMClient* create_nm_client() {
    NMClient *client;
    GError *error = NULL;

    g_info ("Now initialising...");
    g_debug ("INIT: NetworkManager client.");

    if ((client = nm_client_new (NULL, &error)) == 0) {
        g_critical ("Error creating NMClient. Please report issue.");
        g_critical ("Further information is here: %s", error->message);
        g_error_free (error);

        /* we can't continue now. */
        exit (EXIT_FAILURE);
    }

    g_debug ("INIT: Client created.");

    return client;
}

void check_nm_client (NMClient *client) {
    if (client == NULL) {
        g_critical ("NULL NM Client variable detected! PANIC!");
        exit (EXIT_FAILURE);
    }

    if (nm_client_get_nm_running (client) == -1) {
        g_critical ("NetworkManager is NOT running! Halt.");
        exit (EXIT_FAILURE);
    }
}

int
main (void) {
    NMClient *client;
    const GPtrArray *devices;
    guint i;

    client = create_nm_client ();
    check_nm_client (client);

    devices = nm_client_get_all_devices (client);

    if (devices == NULL || devices->len <= 0) {
        g_critical ("No network devices detected.");
        return EXIT_FAILURE;
    }

    for (i = 0; i < devices->len; i++) {
        NMDevice *device;
        const GPtrArray *access_points;
        guint ap;

        device = devices->pdata[i];

        if (device == NULL) {
            g_error ("NULL value detected. (Device). Exiting.");
            return EXIT_SUCCESS;
        }

        if (! NM_IS_DEVICE_WIFI (device)) {
            /* this device isn'ts not a WiFi device.
             * No need to emit anything. */
            continue;
        }

        if (NM_IS_DEVICE_WIFI (device)) {
            nm_device_wifi_request_scan(
                ((NMDeviceWifi *) device),
                NULL,
                NULL);

            access_points = nm_device_wifi_get_access_points (NM_DEVICE_WIFI (device));

            for (ap = 0; ap < access_points->len; ap++) {
                NMAccessPoint *access_point;
                GBytes *access_point_SSID_GBytes;
                gsize len;
                guint8 *bytes;
                guint8 signal_strength;
                char *access_point_SSID_str;
                const char *access_point_BSSID_str;
                const char *bars;

                access_point = access_points->pdata[ap];
                access_point_SSID_GBytes = nm_access_point_get_ssid(access_point);

                if (access_point_SSID_GBytes == NULL) {
                    /* this is an empty result
                     * not an error, continue */
                    continue;
                }

                signal_strength = nm_access_point_get_strength (access_point);
                access_point_BSSID_str = nm_access_point_get_bssid (access_point);
                bytes = g_bytes_unref_to_data (access_point_SSID_GBytes, &len);
                access_point_SSID_str = nm_utils_ssid_to_utf8(bytes, len);
                bars = nm_utils_wifi_strength_bars (signal_strength);

                g_print ("WAP SSID: %s || WAP BSSID: %s || WAP strength: %d%% || Bars: %s\n",
                        access_point_SSID_str,
                        access_point_BSSID_str,
                        signal_strength,
                        bars);
            }
        }

    }

    return EXIT_SUCCESS;
}
