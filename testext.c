#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_testext.h"
#include "testext_obj.h"


ZEND_BEGIN_ARG_INFO(arginfo_TestExtObj___construct, 0)
	ZEND_ARG_INFO(0, is_loser)
ZEND_END_ARG_INFO();

static zend_function_entry testext_functions[] = {
	PHP_ME(TestExtObj, __construct, 			arginfo_TestExtObj___construct, 			ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
	PHP_ME(TestExtObj, isLoser, 				NULL, 							ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(testext)
{
	// Register TestExtObj class
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "TestExtObj", testext_functions);
	TestExtObj_ce = zend_register_internal_class(&ce TSRMLS_CC);
	TestExtObj_ce->create_object = TestExtObj_object_new;
	memcpy(&TestObjExt_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	TestExtObj_handlers.clone_obj = NULL;
	return SUCCESS;
}


zend_module_entry testext_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_TESTEXT_EXTNAME,
	testext_functions,
	PHP_MINIT(testext),
	NULL,
	NULL,
	NULL,
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_TESTEXT_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_TESTEXT
ZEND_GET_MODULE(testext)
#endif

