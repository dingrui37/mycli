/****************************************************************
 *
 *        Copyright 2013, Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 ***************************************************************/

#ifndef __UCLI_UTIL_H__
#define __UCLI_UTIL_H__


#include <bfutils/uCli/ucli_config.h>

uint8_t* ucli_util_data_from_string(const char* string, int* size);
char* ucli_util_data_to_string(ucli_context_t* uc, uint8_t* data, int len,
                               int columns);


#endif /* __UCLI_UTIL_H__ */
