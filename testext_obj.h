#ifndef TESTEXT_OBJ_H
#define TESTEXT_OBJ_H

// Methods for TestExtObj
PHP_METHOD(TestExtObj, __construct);
PHP_METHOD(TestExtObj, isLoser);

// Class structure definition for TestExtObj
typedef struct _TestExtObj_object {
	zend_object std;
	int is_loser;
} TestExtObj_object;

// Constructor and destructor functions for TestExtObj
static void TestExtObj_object_dtor(void *object, zend_object_handle handle TSRMLS_DC);
zend_object_value TestExtObj_object_new(zend_class_entry *ce TSRMLS_DC);

// external linkage variables
extern zend_object_handlers TestExtObj_handlers;
extern zend_class_entry *TestExtObj_ce;

// other random bits
struct MemoryStruct {
	char *memory;
	size_t size;
};

#endif /* TESTEXT_OBJ_H */
