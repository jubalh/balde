/*
 * balde: A microframework for C based on GLib and bad intentions.
 * Copyright (C) 2013-2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <glib.h>
#include <balde/template-private.h>


void
test_template_generate_source_without_vars(void)
{
    gchar *rv = balde_template_generate_source("bola", "ads qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads qwe\";\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup(balde_template_bola_format);\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}

void
test_template_generate_source_single_var(void)
{
    gchar *rv = balde_template_generate_source("bola", "ads {{ guda }} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s qwe\";\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_multiple_vars(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }} {{ bola }} {{balde}} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s %s %s qwe\";\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"),\n"
        "        balde_response_get_tmpl_var(response, \"bola\"),\n"
        "        balde_response_get_tmpl_var(response, \"balde\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_multiple_vars_and_lines(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }}\n"
        "\n"
        "{{ bola }}\n"
        "{{balde}} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s\\n\\n%s\\n%s qwe\";\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"),\n"
        "        balde_response_get_tmpl_var(response, \"bola\"),\n"
        "        balde_response_get_tmpl_var(response, \"balde\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_with_percent(void)
{
    gchar *rv = balde_template_generate_source("bola", "ad %s % {{ guda }} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ad %%s %% %s qwe\";\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_header(void)
{
    gchar *rv = balde_template_generate_header("bola");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#ifndef __bola_balde_template\n"
        "#define __bola_balde_template\n"
        "\n"
        "#include <balde.h>\n"
        "\n"
        "extern void balde_template_bola(balde_response_t *response);\n"
        "\n"
        "#endif\n");
    g_free(rv);
}


void
test_template_get_name(void)
{
    gchar *rv = balde_template_get_name("bola.guda.ação.html");
    g_assert_cmpstr(rv, ==, "bola_guda_a____o");
    g_free(rv);
}


int
main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/template/generate_source_without_vars",
        test_template_generate_source_without_vars);
    g_test_add_func("/template/generate_source_single_var",
        test_template_generate_source_single_var);
    g_test_add_func("/template/generate_source_multiple_vars",
        test_template_generate_source_multiple_vars);
    g_test_add_func("/template/generate_source_multiple_vars_and_lines",
        test_template_generate_source_multiple_vars_and_lines);
    g_test_add_func("/template/generate_source_with_percent",
        test_template_generate_source_with_percent);
    g_test_add_func("/template/generate_header",
        test_template_generate_header);
    g_test_add_func("/template/get_name", test_template_get_name);
    return g_test_run();
}
