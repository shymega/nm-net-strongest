/*
 * Copyright 2019-2024 Dom Rodriguez (shymega)

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef UTILS_H
#define UTILS_H

#include <glib-2.0/glib.h>
#include <glib-2.0/gio/gio.h>
#include <libnm/NetworkManager.h>

NMClient *create_nm_client();
void check_nm_client(NMClient *client);

#endif /* UTILS_H_ */
