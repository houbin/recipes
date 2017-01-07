#include "leptjson.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#define EXPECT(c, ch) do{assert(*c->json == (ch));} while(0)

lept_type lept_get_type(const lept_value *v)
{
	return v->type;
}

int lept_get_boolean(const lept_value *v)
{
	if (v->type == LEPT_TRUE)
		return 1;
	return 0;
}

void lept_set_boolean(lept_value *v, int b)
{
	if (b == 0)
		v->type = LEPT_FALSE;
	else
		v->type = LEPT_TRUE;
}

double lept_get_number(const lept_value *v)
{
	return v->u.n;
}

void lept_set_number(lept_value *v, double n)
{
	v->u.n = n;
}

const char *lept_get_string(const lept_value *v)
{
	return v->u.s.s;
}

size_t lept_get_string_length(const lept_value *v)
{
	return v->u.s.len;
}

void lept_set_string(lept_value *v, const char *s, size_t len)
{
	assert(v!= NULL && (s!= NULL || len == 0));

	lept_free(v);

	v->u.s.s = (char *)malloc(len+1);
	memcpy(v->u.s.s, s, len);
	v->u.s.s[len] = 0;
	v->u.s.len = len;
	v->type = LEPT_STRING;

	return;
}

/* ws = *(%x20 / %x09 / %x0A / %x0d) */
static void lept_parse_whitespace(lept_context *ct)
{
	const char *c = ct->json;

	while (c[0] == ' ' || c[0] == '\t' || c[0] == '\n' || c[0] == '\r')
		c++;

	ct->json = c;
	return;
}

static int lept_parse_literal(lept_context *ct, lept_value *v, const char *literal, lept_type type)
{
	int i = 0;
	const char *c = ct->json;

	for(i = 0; literal[i]; i++)
	{
		if (c[i] != literal[i])
			return LEPT_PARSE_INVALID_VALUE;
	}

	v->type = type;
	ct->json += i;
	return LEPT_PARSE_OK;
}

#define IS_DIGITAL(c) (c>='0' && c<='9')
#define IS_DIGITAL_1_TO_9(c) (c>='1' && c<='9')

int lept_parse_number(lept_context *ct, lept_value *v)
{
	const char *ptr = ct->json;

	/* validate '.' */
	if (ptr[0] == '-') ptr++;

	/* validate integer */
	if (ptr[0] == '0')
		ptr++;
	else
	{
		if (!IS_DIGITAL_1_TO_9(ptr[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for (; IS_DIGITAL(ptr[0]); ptr++);
	}

	/* validate '.' */
	if (ptr[0] == '.')
	{
		ptr++;
		if (!IS_DIGITAL(ptr[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for(; IS_DIGITAL(ptr[0]); ptr++);
	}

	/* validate 'e' or 'E' */
	if (ptr[0] == 'e' || ptr[0] == 'E')
	{
		ptr++;

		/*  validate '+' or '-' */
		if (ptr[0] == '+' || ptr[0] == '-') ptr++;

		if (!IS_DIGITAL(ptr[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for(; IS_DIGITAL(ptr[0]); ptr++);
	}


	v->u.n = strtod(ct->json, NULL);
	if (errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL))
		return LEPT_PARSE_NUMBER_TOO_BIG;

	v->type = LEPT_NUMBER;
	ct->json = ptr;

	return LEPT_PARSE_OK;
}

#ifndef LEPT_PARSE_STACK_INIT_SIZE
#define LEPT_PARSE_STACK_INIT_SIZE 256
#endif

static void *lept_context_push(lept_context *ct, size_t size)
{
	void *ret;
	if (ct->top + size >= ct->size)
	{
		if (ct->size == 0)
		{
			ct->size = LEPT_PARSE_STACK_INIT_SIZE;
		}

		while (ct->top + size >= ct->size)
		{
			/* ct->size * 1.5 */
			ct->size += ct->size>>1;
		}

		ct->stack = (char *)realloc(ct->stack, ct->size);
	}

	ret = ct->stack + ct->top;
	ct->top += size;

	return ret;
}

#define PUTC(ct, ch) do{ *(char*)lept_context_push(ct, sizeof(char)) = (ch);}while(0)

static void *lept_context_pop(lept_context *ct, size_t size)
{
	assert(ct->top >= size);
	return (ct->stack + (ct->top -= size));
}

const char *lept_parse_hex4(const char *p, unsigned *u)
{
	int i = 0;
	*u = 0;

	for (i = 0; i < 4; i++)
	{
		char ch = *p++;
		*u <<= 4;

		if (ch >= '0' && ch <= '9')     	*u |= (ch - '0');
		else if (ch >= 'a' && ch <= 'f') 	*u |= (ch - 'a' + 10);
		else if (ch >= 'A' && ch <= 'F') 	*u |= (ch - 'A' + 10);
		else								return NULL;
	}

	return p;
}

int lept_encode_utf8(lept_context *ct, unsigned u)
{
	assert(u <= 0x10ffff);

	if (u <= 0x7f)
		PUTC(ct, u & 0xff);
	else if (u >= 0x80 && u <= 0x7ff)
	{
		PUTC(ct, (u >> 6) | 0xc0);
	 	PUTC(ct, (u & 0x3f) | 0x80);
	}
	else if (u >= 0x800 && u <= 0xffff)
	{
		PUTC(ct, (u >> 12) | 0xe0);
		PUTC(ct, ((u >> 6) & 0x3f) | 0x80);
		PUTC(ct, (u & 0x3f) | 0x80);
	}
	else if (u >= 0x10000 && u <= 0x10ffff)
	{
		PUTC(ct, ((u >> 18) & 0x7) | 0xf0);
		PUTC(ct, ((u >> 12) & 0x3f) | 0x80);
		PUTC(ct, ((u >> 6) & 0x3f) | 0x80);
		PUTC(ct, (u & 0x3f) | 0x80);
	}

	return 0;
}

int lept_parse_string(lept_context *ct, lept_value *v)
{
	size_t head = ct->top;
	const char *p = ct->json + 1;
	size_t len;
    unsigned u;
	unsigned l;

	while(1)
	{
		char ch = *p++;
		switch (ch)
		{
			case '"':
				/* end of string */
				len = ct->top - head;
	   			lept_set_string(v, (const char*)lept_context_pop(ct, len), len);
				ct->json = p;
				return LEPT_PARSE_OK;
			case '\0':
				ct->top = head;
				return LEPT_PARSE_MISS_QUOTATION_MASK;
			case '\\':
				switch(*p++)
				{
					case '\"': 
						PUTC(ct, '\"');
					  	break;
					case '\\':
						PUTC(ct, '\\');
						break;
					case '/':
						PUTC(ct, '/'); break; case 'b': PUTC(ct, '\b'); break; case 'f': PUTC(ct, '\f');
						break;
					case 'n':
						PUTC(ct, '\n');
						break;
					case 'r':
						PUTC(ct, '\r');
						break;
					case 't':
						PUTC(ct, '\t');
						break;
					case 'u':
						if (!(p = lept_parse_hex4(p, &u)))
							return LEPT_PARSE_INVALID_UNICODE_HEX;

						/* TODO surrogate handing */
						if (u >= 0xD800 && u < 0xDBFF)
						{
							if (*p++ != '\\' || *(p++) != 'u')
							{
								return LEPT_PARSE_INVALID_UNICODE_HEX;
							}

							if (!(p = lept_parse_hex4(p, &l)))
								return LEPT_PARSE_INVALID_UNICODE_SURROGATE;

							if (!(l >= 0xDC00 && l <= 0xDFFF))
							{
								return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
							}

							u = 0x10000 + (u - 0xD800) * 0x400 + (l - 0xDC00);
						}

						lept_encode_utf8(ct, u);
						break;
					default:
						ct->top = head;
						return LEPT_PARSE_INVALID_STRING_ESCAPE;
				}
				break;
			default:
				if ((unsigned char)ch < 0x20)
				{
					ct->top = head;
					return LEPT_PARSE_INVALID_STRING_CHAR;	
				}

				PUTC(ct, ch);
		}
	}
}

int lept_parse_value(lept_context *ct, lept_value *v)
{
	switch(*ct->json)
	{
		case 'n': 	return lept_parse_literal(ct, v, "null", LEPT_NULL);
		case 't':	return lept_parse_literal(ct, v, "true", LEPT_TRUE);
		case 'f': 	return lept_parse_literal(ct, v, "false", LEPT_FALSE);
		case '\0': 	return LEPT_PARSE_EXPECT_VALUE;
		case '"': return lept_parse_string(ct, v);
		default: 	return lept_parse_number(ct, v);
	}
}

int lept_parse(lept_value *v, const char *json)
{
	int ret = 0;
	lept_context ct;

	assert(v != NULL);

	ct.json = json;
	ct.stack = NULL;
	ct.size = ct.top = 0;
	lept_init(v);

	lept_parse_whitespace(&ct);
	while ((ret = lept_parse_value(&ct, v)) == LEPT_PARSE_OK)
	{
		lept_parse_whitespace(&ct);
		if (ct.json[0] != '\0')
		{
			v->type = LEPT_NULL;
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
		else
			ret = LEPT_PARSE_OK;

		break;
	}
	assert(ct.top == 0);
	if (ct.stack != NULL)
	{
		free(ct.stack);
	}

	return ret;
}

void lept_free(lept_value *v)
{
	if (v->type == LEPT_STRING && v->u.s.s != NULL)
	{
		free(v->u.s.s);
		v->u.s.s = NULL;
	}

	v->type = LEPT_NULL;
}


