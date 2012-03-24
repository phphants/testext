#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "php.h"
#include "php_testext.h"
#include "testext_obj.h"

// Object variables
zend_object_handlers TestExtObj_handlers;
zend_class_entry *TestExtObj_ce;

// Static methods for CURL processing
//static void *myrealloc(void *ptr, size_t size);
//static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

// Destructor
static void TestExtObj_object_dtor(void *object, zend_object_handle handle TSRMLS_DC)
{
	TestExtObj_object *intern = (TestExtObj_object *)object;
	zend_object_std_dtor(&(intern->std) TSRMLS_CC);

	efree(object);
}

// Constructor
zend_object_value TestExtObj_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	TestExtObj_object *intern;

	intern = ecalloc(1, sizeof(TestExtObj_object));
	zend_object_std_init(&(intern->std), ce TSRMLS_CC);
	zend_hash_copy(intern->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval *));

	intern->is_loser = 0;

	retval.handle = zend_objects_store_put(intern, TestExtObj_object_dtor, NULL, NULL TSRMLS_CC);
	retval.handlers = &TestExtObj_handlers;
	return retval;
}

static void *myrealloc(void *ptr, size_t size)
{
	/* There might be a realloc() out there that doesn't like reallocing
		NULL pointers, so we take care of it here */
	if(ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

PHP_METHOD(TestExtObj, __construct)
{
	TestExtObj_object *intern;
	int is_loser = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &is_loser) == SUCCESS)
	{
		intern = (TestExtObj_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
		intern->is_loser = is_loser;
	}
}

PHP_METHOD(TestExtObj, isLoser)
{
	TestExtObj_object *intern = (TestExtObj_object*)zend_object_store_get_object(getThis() TSRMLS_CC);

	if(intern->is_loser == 1)
	{
		RETURN_TRUE;
	}
	else
	{
		RETURN_TRUE;
	}
}

