#include <stdio.h>
#include "leptjson.h"
#include <string.h>

static int main_ret = 0;
static int test_pass = 0;
static int test_count = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do\
	{\
		test_count++;\
		if (equality)\
			test_pass++;\
		else\
		{\
			fprintf(stderr, "%s:%d: expect: " format ", actual format: " format "\n", __FILE__, __LINE__, expect, actual);\
			main_ret = 1;\
		}\
	}\
	while(0);

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual, "%f")
#define EXPECT_EQ_STRING(expect, actual, len) EXPECT_EQ_BASE(memcmp(expect, actual, len) == 0, expect, actual, "%s")

#define TEST_ERROR(error, json) \
	do{\
		lept_value v;\
		v.type = LEPT_NULL;\
		EXPECT_EQ_INT(error, lept_parse(&v, json));\
		EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));\
	}while(0)

#define TEST_OK(error, json, expect_type) \
	do{\
		lept_value v;\
		v.type = LEPT_NULL;\
		EXPECT_EQ_INT(error, lept_parse(&v, json));\
		EXPECT_EQ_INT(expect_type, lept_get_type(&v));\
	}while(0)

#define TEST_NUMBER(expect, json) \
	do{\
		lept_value v;\
		v.type = LEPT_NULL;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(LEPT_NUMBER, lept_get_type(&v));\
		EXPECT_EQ_DOUBLE(expect, lept_get_number(&v));\
	}while(0)

#define TEST_STRING(expect, json) \
	do{\
		lept_value v;\
		v.type = LEPT_NULL;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(LEPT_STRING, lept_get_type(&v));\
		EXPECT_EQ_STRING(expect, lept_get_string(&v), lept_get_string_length(&v));\
	   }while(0)

static void test_parse_null()
{
	TEST_OK(LEPT_PARSE_OK, "null", LEPT_NULL);
}

static void test_parse_true()
{
	TEST_OK(LEPT_PARSE_OK, "true", LEPT_TRUE);
}

static void test_parse_false()
{
	TEST_OK(LEPT_PARSE_OK, "false", LEPT_FALSE);
}

static void test_parse_expect_value()
{
	TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, "");
	TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, " ");
}

static void test_parse_invalid_value()
{
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nul");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "?");

	/* invalid double */
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+0");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+1");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, ".123");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "1.");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "INF");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "inf");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "MAN");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "man");

}

static void test_parse_root_not_singular()
{
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "null x"); 
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
}

static void test_parse_number()
{
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");

	TEST_NUMBER(0.0, "0.0");
	TEST_NUMBER(0.0, "-0.0");

	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");

	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");

	TEST_NUMBER(3.1415926, "3.1415926");
	TEST_NUMBER(-3.1415926, "-3.1415926");

	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");

	TEST_NUMBER(-1E10, "-1E10");
	TEST_NUMBER(-1E+10, "-1E+10");
	TEST_NUMBER(-1E-10, "-1E-10");

	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1e+10, "1e+10");
	TEST_NUMBER(1e-10, "1e-10");

	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1e+10, "-1e+10");
	TEST_NUMBER(-1e-10, "-1e-10");

	TEST_NUMBER(1.234E10, "1.234E10");
	TEST_NUMBER(-1.234E10, "-1.234E10");

	TEST_NUMBER(0.0, "1E-1000"); /* must underflow */

	TEST_NUMBER(0.0, "0.0e123");

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
	TEST_NUMBER( 4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
	TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	TEST_NUMBER( 2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
	TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	TEST_NUMBER( 2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
	TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	TEST_NUMBER( 1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
	TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

static void test_parse_number_too_big()
{
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e1000");
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
}

void test_access_string()
{
	lept_value v;
	lept_free(&v);
	lept_init(&v);

	lept_set_string(&v, "", 0);
	EXPECT_EQ_STRING("", lept_get_string(&v), sizeof(""));

	lept_set_string(&v, "null", sizeof("null"));
	EXPECT_EQ_STRING("null", lept_get_string(&v), sizeof("null"));

	lept_set_string(&v, "hello", sizeof("hello"));
	EXPECT_EQ_STRING("hello", lept_get_string(&v), sizeof("hello"));
}

void test_parse_string()
{
	TEST_STRING("houbin", "\"houbin\"");
	TEST_STRING("", "\"\"");
	TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
	TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
}

static void test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();
	test_parse_expect_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
	test_parse_number();
	test_parse_number_too_big();

	test_access_string();
	test_parse_string();
}

int main()
{
	test_parse();
	printf("%d/%d (%3.2f%%)passed\n", test_pass, test_count, test_pass * 100.0 / test_count);

	return 0;
}

