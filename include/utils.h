#ifndef UTILS_H_
#define UTILS_H_

#include <glib-2.0/glib.h>
#include <glib-2.0/gio/gio.h>
#include <libnm/NetworkManager.h>

NMClient *create_nm_client();
void check_nm_client(NMClient *client);

#endif /* UTILS_H_ */
