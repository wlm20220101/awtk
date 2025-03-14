﻿#include "tkc/str.h"
#include "tkc/object_default.h"
#include "gtest/gtest.h"
#include <string>

using std::string;

TEST(Str, demo) {
  str_t s;
  str_init(&s, 0);

  str_append(&s, "abc");
  str_append(&s, "123");

  str_reset(&s);
}

TEST(Str, basic) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(s->size, 0u);

  ASSERT_EQ(str_set(s, "hello"), RET_OK);
  ASSERT_EQ(str_eq(s, "hello"), TRUE);

  ASSERT_EQ(str_append(s, " world"), RET_OK);
  ASSERT_EQ(str_eq(s, "hello world"), TRUE);

  ASSERT_EQ(str_to_upper(s), RET_OK);
  ASSERT_EQ(str_eq(s, "HELLO WORLD"), TRUE);

  ASSERT_EQ(str_to_lower(s), RET_OK);
  ASSERT_EQ(str_eq(s, "hello world"), TRUE);

  ASSERT_EQ(str_replace(s, "o", "ooo"), RET_OK);
  ASSERT_EQ(str_eq(s, "hellooo wooorld"), TRUE);

  ASSERT_EQ(str_replace(s, "ooo", "xxx"), RET_OK);
  ASSERT_EQ(str_eq(s, "hellxxx wxxxrld"), TRUE);

  ASSERT_EQ(str_trim_left(s, "hel"), RET_OK);
  ASSERT_EQ(str_eq(s, "xxx wxxxrld"), TRUE);

  ASSERT_EQ(str_trim_right(s, "rld"), RET_OK);
  ASSERT_EQ(str_eq(s, "xxx wxxx"), TRUE);

  ASSERT_EQ(str_trim(s, "x "), RET_OK);
  ASSERT_EQ(str_eq(s, "w"), TRUE);

  ASSERT_EQ(str_trim_right(s, "w"), RET_OK);
  ASSERT_EQ(str_eq(s, ""), TRUE);

  ASSERT_EQ(str_set(s, "test.png"), RET_OK);
  ASSERT_EQ(str_start_with(s, "test"), TRUE);
  ASSERT_EQ(str_end_with(s, ".png"), TRUE);

  str_reset(s);
}

TEST(Str, set_with_len) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(str_set_with_len(s, "hello world", 0), RET_OK);
  ASSERT_EQ(str_eq(s, ""), TRUE);

  ASSERT_EQ(str_set_with_len(s, "hello world", 1), RET_OK);
  ASSERT_EQ(str_eq(s, "h"), TRUE);

  ASSERT_EQ(str_set_with_len(s, "hello world", 5), RET_OK);
  ASSERT_EQ(str_eq(s, "hello"), TRUE);

  str_reset(s);
}

TEST(Str, decode_xml_entity) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(str_decode_xml_entity(s, "a&lt;b"), RET_OK);
  ASSERT_EQ(str_eq(s, "a<b"), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "a&lt;b&gt;c"), RET_OK);
  ASSERT_EQ(str_eq(s, "a<b>c"), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "&quot;a&lt;b&gt;c&quot;"), RET_OK);
  ASSERT_EQ(str_eq(s, "\"a<b>c\""), TRUE);

  ASSERT_EQ(str_decode_xml_entity(s, "&quot;a&lt;b&gt;c&quot;&amp;&amp;"), RET_OK);
  ASSERT_EQ(str_eq(s, "\"a<b>c\"&&"), TRUE);

  str_reset(s);
}

TEST(Str, value) {
  str_t str;
  value_t v;
  str_t* s = str_init(&str, 0);

  value_set_int(&v, 100);
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("100"));

  value_set_str(&v, "123");
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("123"));

  value_set_wstr(&v, L"abc");
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("abc"));

  value_set_float32(&v, 100);
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("100.000000"));

  value_set_double(&v, 100);
  ASSERT_EQ(str_from_value(s, &v), RET_OK);
  ASSERT_EQ(string(s->str), string("100.000000"));

  str_reset(s);
}

TEST(Str, insert) {
  str_t str;
  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_insert(s, 0, "abc"), RET_OK);
  ASSERT_EQ(string(s->str), "abc");

  ASSERT_EQ(str_insert(s, 0, "abc"), RET_OK);
  ASSERT_EQ(string(s->str), "abcabc");

  ASSERT_EQ(str_insert(s, 1, "A"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbcabc");

  ASSERT_EQ(str_insert(s, 3, "B"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbBcabc");

  ASSERT_EQ(str_insert(s, 8, "C"), RET_OK);
  ASSERT_EQ(string(s->str), "aAbBcabcC");

  str_reset(s);
}

TEST(Str, remove) {
  str_t str;
  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 0, 3), RET_OK);
  ASSERT_EQ(string(s->str), "");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 0, 1), RET_OK);
  ASSERT_EQ(string(s->str), "bc");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 1, 1), RET_OK);
  ASSERT_EQ(string(s->str), "ac");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_remove(s, 2, 1), RET_OK);
  ASSERT_EQ(string(s->str), "ab");

  str_reset(s);
}

TEST(Str, unescap) {
  str_t str;
  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_set(s, "\\"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "\\");

  ASSERT_EQ(str_set(s, "abc"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "abc");

  ASSERT_EQ(str_set(s, "a\\nbc"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "a\nbc");

  ASSERT_EQ(str_set(s, "\\ra\\rbc\\r"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "\ra\rbc\r");

  ASSERT_EQ(str_set(s, "\\ta\\tbc\\t"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "\ta\tbc\t");

  ASSERT_EQ(str_set(s, "\\\\a\\\\bc\\\\"), RET_OK);
  ASSERT_EQ(str_unescape(s), RET_OK);
  ASSERT_EQ(string(s->str), "\\a\\bc\\");

  str_reset(s);
}

TEST(Str, expand_vars) {
  str_t str;
  tk_object_t* vars = object_default_create();
  tk_object_set_prop_int(vars, "x", 100);
  tk_object_set_prop_int(vars, "y", 200);
  tk_object_set_prop_int(vars, "w", 300);
  tk_object_set_prop_int(vars, "h", 400);
  tk_object_set_prop_str(vars, "os", "mac");

  str_t* s = str_init(&str, 0);

  ASSERT_EQ(str_expand_vars(s, "${x}", vars), RET_OK);
  ASSERT_STREQ(s->str, "100");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "${x},${y}", vars), RET_OK);
  ASSERT_STREQ(s->str, "100,200");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "img-${x},${y}", vars), RET_OK);
  ASSERT_STREQ(s->str, "img-100,200");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "img-${x},${y},${w},${h}-${os}", vars), RET_OK);
  ASSERT_STREQ(s->str, "img-100,200,300,400-mac");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "${$x+$y}", vars), RET_OK);
  ASSERT_STREQ(s->str, "300");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "${$os+$os}", vars), RET_OK);
  ASSERT_STREQ(s->str, "macmac");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "${($x+$y)+$os}", vars), RET_OK);
  ASSERT_STREQ(s->str, "300mac");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "${abc}", vars), RET_OK);
  ASSERT_STREQ(s->str, "abc");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "123${abc}456", vars), RET_OK);
  ASSERT_STREQ(s->str, "123abc456");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "123${}456", vars), RET_OK);
  ASSERT_STREQ(s->str, "123456");

  str_set(s, "");
  ASSERT_EQ(str_expand_vars(s, "123${abc+$x}456", vars), RET_OK);
  ASSERT_STREQ(s->str, "123abc100456");

  tk_object_unref(vars);
  str_reset(s);
}

TEST(Str, from_wstr) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 0);

  ASSERT_EQ(s->size, 0u);
  str_from_wstr(s, L"123456");
  ASSERT_STREQ(s->str, "123456");

  str_from_wstr_with_len(s, L"123456", 3);
  ASSERT_STREQ(s->str, "123");

  str_from_wstr_with_len(s, L"123456", 0);
  ASSERT_STREQ(s->str, "");

  str_reset(s);
}

TEST(Str, json0) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);

  ASSERT_EQ(str_append_json_str(&str, "\"zhang\r\nshan\""), RET_OK);
  ASSERT_STREQ(str.str, "\"\\\"zhang\\r\\nshan\\\"\"");

  str_reset(s);
}


TEST(Str, json) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);

  ASSERT_EQ(str_append_char(&str, '{'), RET_OK);
  ASSERT_EQ(str_append_json_str_pair(&str, "name", "zhangshan"), RET_OK);
  ASSERT_EQ(str_append_char(&str, ','), RET_OK);

  ASSERT_EQ(str_append_json_int_pair(&str, "age", 100), RET_OK);
  ASSERT_EQ(str_append_char(&str, ','), RET_OK);

  ASSERT_EQ(str_append_json_double_pair(&str, "weight", 60.5), RET_OK);
  ASSERT_EQ(str_append_char(&str, ','), RET_OK);

  ASSERT_EQ(str_append_json_bool_pair(&str, "gender", TRUE), RET_OK);
  ASSERT_EQ(str_append_char(&str, '}'), RET_OK);

  ASSERT_STREQ(str.str, "{\"name\":\"zhangshan\",\"age\":100,\"weight\":60.5000,\"gender\":true}");

  str_reset(s);
}

TEST(Str, append_more1) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  ASSERT_EQ(str_append_more(s, "123", NULL), RET_OK);
  ASSERT_STREQ(s->str, "123");

  str_reset(s);
}

TEST(Str, append_more2) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  ASSERT_EQ(str_append_more(s, "123", "abc", NULL), RET_OK);
  ASSERT_STREQ(s->str, "123abc");

  str_reset(s);
}

TEST(Str, encode_hex_basic) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  uint8_t data[] = {1, 0x01, 0x0a, 0x2a};
  ASSERT_EQ(str_encode_hex(s, data, sizeof(data), NULL), RET_OK);
  ASSERT_STREQ(s->str, "01010a2a");
  str_reset(s);
}

TEST(Str, encode_hex_upper) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  uint8_t data[] = {1, 0x01, 0x0a, 0x2a};
  ASSERT_EQ(str_encode_hex(s, data, sizeof(data), "%02X"), RET_OK);
  ASSERT_STREQ(s->str, "01010A2A");
  str_reset(s);
}

TEST(Str, encode_hex_sep) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  uint8_t data[] = {1, 0x01, 0x0a, 0x2a};
  ASSERT_EQ(str_encode_hex(s, data, sizeof(data), "%02X "), RET_OK);
  ASSERT_STREQ(s->str, "01 01 0A 2A ");
  str_reset(s);
}

TEST(Str, encode_hex_sep1) {
  str_t str;
  str_t* s = NULL;
  s = str_init(&str, 100);
  uint8_t data[] = {1, 0x01, 0x0a, 0x2a};
  ASSERT_EQ(str_encode_hex(s, data, sizeof(data), "0x%02X "), RET_OK);
  ASSERT_STREQ(s->str, "0x01 0x01 0x0A 0x2A ");
  str_reset(s);
}

TEST(Str, decode_hex) {
  str_t str;
  ret_t ret;
  uint8_t data[6];

  memset(data, 0, sizeof(data));
  str_init(&str, 100);
  str_append(&str, "fF fe 12    0x65");
  str_decode_hex(&str, data, sizeof(data));
  ASSERT_TRUE(data[0] == 0xff && data[1] == 0xfe && data[2] == 0x12 && data[3] == 0x65);

  str_append(&str, "ya    e8");
  str_decode_hex(&str, data, sizeof(data));
  ASSERT_TRUE(data[0] == 0xff && data[1] == 0xfe && data[2] == 0x12 && data[3] == 0x65);
  ASSERT_TRUE(data[4] == 0 && data[5] == 0xe8);

  ret = str_append(&str, "6b  33");
  ASSERT_EQ(ret, RET_OK);
  str_decode_hex(&str, data, sizeof(data));
  ASSERT_TRUE(data[0] == 0xff && data[1] == 0xfe && data[2] == 0x12 && data[3] == 0x65);
  ASSERT_TRUE(data[4] == 0);
  ASSERT_EQ(data[5], 0xe8);

  str_reset(&str);
}

TEST(Str, append_n_chars) {
  str_t str;

  str_init(&str, 100);

  str_clear(&str);
  ASSERT_EQ(str_append_n_chars(&str, ' ', 1), RET_OK);
  ASSERT_STREQ(str.str, " ");

  str_clear(&str);
  ASSERT_EQ(str_append_n_chars(&str, ' ', 2), RET_OK);
  ASSERT_STREQ(str.str, "  ");

  str_clear(&str);
  ASSERT_EQ(str_append_n_chars(&str, ' ', 5), RET_OK);
  ASSERT_STREQ(str.str, "     ");
  str_reset(&str);
}

TEST(Str, common_prefix) {
  str_t str;

  str_init(&str, 100);

  str_set(&str, "abc.cde.123");
  ASSERT_EQ(str_common_prefix(&str, "abc.123"), RET_OK);
  ASSERT_STREQ(str.str, "abc.");

  str_set(&str, "abc.cde.123");
  ASSERT_EQ(str_common_prefix(&str, "abc.c123"), RET_OK);
  ASSERT_STREQ(str.str, "abc.c");

  str_set(&str, "abc.cde.123");
  ASSERT_EQ(str_common_prefix(&str, "c123"), RET_OK);
  ASSERT_STREQ(str.str, "");

  str_set(&str, "abc.cde.123");
  ASSERT_EQ(str_common_prefix(&str, "abc.cde.123"), RET_OK);
  ASSERT_STREQ(str.str, "abc.cde.123");

  str_set(&str, "");
  ASSERT_EQ(str_common_prefix(&str, "abc.cde.123"), RET_OK);
  ASSERT_STREQ(str.str, "");

  str_reset(&str);
}

TEST(Str, int64) {
  str_t str;
  str_init(&str, 100);
  ASSERT_EQ(str_append_int64(&str, 123567890123), RET_OK);
  ASSERT_STREQ(str.str, "123567890123");
  str_reset(&str);

  ASSERT_EQ(str_append_int64(&str, -123567890123), RET_OK);
  ASSERT_STREQ(str.str, "-123567890123");
  str_reset(&str);
}

TEST(Str, uint64) {
  str_t str;
  str_init(&str, 100);
  ASSERT_EQ(str_append_uint64(&str, 123567890123), RET_OK);
  ASSERT_STREQ(str.str, "123567890123");
  str_reset(&str);

  ASSERT_EQ(str_append_uint64(&str, -1), RET_OK);
  ASSERT_STREQ(str.str, "18446744073709551615");
  str_reset(&str);
}

TEST(Str, reverse) {
  str_t str;
  str_init(&str, 100);
  str_set(&str, "ABCD");
  ASSERT_EQ(str_reverse(&str), RET_OK);
  ASSERT_STREQ(str.str, "DCBA");

  str_set(&str, "A");
  ASSERT_EQ(str_reverse(&str), RET_OK);
  ASSERT_STREQ(str.str, "A");

  str_set(&str, "AB");
  ASSERT_EQ(str_reverse(&str), RET_OK);
  ASSERT_STREQ(str.str, "BA");

  str_set(&str, "ABC");
  ASSERT_EQ(str_reverse(&str), RET_OK);
  ASSERT_STREQ(str.str, "CBA");

  str_reset(&str);
}

TEST(Str, count) {
  str_t str;
  str_init(&str, 100);
  str_set(&str, "ABCD");
  ASSERT_EQ(str_count(&str, "BC"), 1);
  ASSERT_EQ(str_count(&str, "ABC"), 1);
  ASSERT_EQ(str_count(&str, "ABCD"), 1);
  ASSERT_EQ(str_count(&str, "ABCDE"), 0);

  str_set(&str, "ABCD ABCD");
  ASSERT_EQ(str_count(&str, "BC"), 2);
  ASSERT_EQ(str_count(&str, "ABC"), 2);
  ASSERT_EQ(str_count(&str, "ABCD"), 2);
  ASSERT_EQ(str_count(&str, "ABCDE"), 0);
  str_reset(&str);
}
