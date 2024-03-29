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

#include <bfutils/uCli/ucli_config.h>
#include <bfutils/uCli/ucli.h>
#include <bfutils/uCli/ucli_argparse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static ucli_status_t
__echo__(const char* pfx, ucli_context_t* uc)
{
    int i;
    printf("%s: ", pfx);
    for(i = 0; i < uc->pargs->count; i++) {
        printf("%s ", uc->pargs->args[i]);
    }
    printf("\n");
    return UCLI_STATUS_OK;
}

#include "modules.c_"


static ucli_status_t
utest_ucli_options__flat__(ucli_context_t* uc)
{
    int i;
    ucli_t* ucli;

    UCLI_COMMAND_INFO(uc,
                      "flat", 0,
                      "Run the flat test.");

    ucli = ucli_create(NULL, NULL, NULL);
    for(i = 0; modules[i]; i++) {
        ucli_module_init(modules[i]);
        ucli_module_add(ucli, modules[i]);
    }
    ucli_run(ucli, "flat", stdin, stdout, stderr);

    ucli_destroy(ucli);
    return UCLI_STATUS_OK;

}

static ucli_status_t
utest_ucli_options__deep__(ucli_context_t* uc)
{
    int i;
    ucli_node_t* last = NULL;
    ucli_t* ucli;

    UCLI_COMMAND_INFO(uc,
                      "deep", 0,
                      "Run the deep test.");

    for(i = sizeof(modules)/sizeof(modules[0]) - 2; i >= 0; i--) {
        ucli_node_t* node;
        ucli_module_init(modules[i]);
        node = ucli_node_create(modules[i]->name, NULL,
                                             modules[i]);
        if(last == NULL) {
            last = node;
        }
        else {
            ucli_node_subnode_add(node, last);
            last = node;
        }
    }

    ucli = ucli_create(NULL, NULL, NULL);
    ucli_node_add(ucli, last);
    ucli_run(ucli, "deep", stdin, stdout, stderr);
    return UCLI_STATUS_OK;
}

static ucli_status_t
utest_ucli_options__ptest__(ucli_context_t* uc)
{
    UCLI_COMMAND_INFO(uc,
                      "ptest", 0,
                      "Run the print test.");

    ucli_printf(uc, "None\n");
    ucli_printf(uc, "%s:%d\n", __FILE__, __LINE__);
    ucli_printf(uc, "boolean(1)=%{bool}\n", 1);
    ucli_printf(uc, "boolean(0)=%{bool}\n", 0);
    ucli_printf(uc, "IPv4 Address=%{ipv4a}\n", 0x0A10FE02);
    ucli_printf(uc, "%s %d %{bool} %p %{ipv4a} %d\n",
                "String1", 1, 0, 0x1, 0x0A10FE02, 10);
    ucli_printf(uc, "%*s %*.*d %{bool}\n", 6, "X", 1, 2, 3, 1);
    ucli_printf(uc, "%{ip4conn}\n", "123.343.2.4", 0x10010);
    return UCLI_STATUS_OK;
}

static ucli_status_t
utest_ucli_options__add3__(ucli_context_t* uc)
{
    int n[3] = {0,0,0};

    UCLI_COMMAND_INFO(uc,
                      "add3", 3,
                      "Add three numbers together.");

    UCLI_ARGPARSE_OR_RETURN(uc, "iii", n, n+1, n+2);
    ucli_printf(uc, "sum=%d\n", n[0]+n[1]+n[2]);
    return UCLI_STATUS_OK;
}


/* <auto.ucli.handlers.start> */
/******************************************************************************
 *
 * These handler table(s) were autogenerated from the symbols in this
 * source file.
 *
 *****************************************************************************/
static ucli_command_handler_f utest_ucli_options_handlers__[] =
{
    utest_ucli_options__flat__,
    utest_ucli_options__deep__,
    utest_ucli_options__ptest__,
    utest_ucli_options__add3__,
    NULL
};
/******************************************************************************/
/* <auto.ucli.handlers.end> */

ucli_module_t options_module =
    {
        "utest",
        NULL,
        utest_ucli_options_handlers__,
        NULL,
        NULL
    };


int main(int argc, char* argv[])
{
    ucli_t* uopts;

    AIM_REFERENCE(argc);

    aim_datatypes_init();
    ucli_init();
    ucli_module_init(&options_module);
    uopts = ucli_create(NULL, &options_module, NULL);
    ucli_dispatch_argv(uopts, &aim_pvs_stdout, argv+1);
    ucli_destroy(uopts);
    ucli_denit();
    return 0;
}



