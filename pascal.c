#include<assert.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

#include <ffi.h>

struct four_int64 {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
};

struct one_integer {
    int32_t value;
};

struct four_int64 return_struct_cdecl();
struct four_int64 return_struct_pascal();
struct four_int64 return_struct_register();
void verify_struct_cdecl(struct four_int64 val);
void verify_struct_pascal(struct four_int64 val);
void verify_struct_register(struct four_int64 val);
struct four_int64 identity_cdecl(struct four_int64 value);
struct four_int64 identity_pascal(struct four_int64 value);
struct four_int64 identity_register(struct four_int64 value);
void verify_callback_cdecl(/* pascal ABI */ void *fn_ptr);
void verify_callback_pascal(/* pascal ABI */ void *fn_ptr);
void verify_callback_register(/* register ABI */ void *fn_ptr);
struct four_int64 register_two_args_return_struct(int32_t a, struct four_int64 b);
struct four_int64 register_three_args_return_struct(int32_t a, int32_t b, struct four_int64 c);
struct four_int64 register_four_args_return_struct(int32_t a, int32_t b, int32_t c, struct four_int64 d);
void verify_two_args_callback_register(void *fn_ptr);
void verify_three_args_callback_register(void *fn_ptr);
void verify_four_args_callback_register(void *fn_ptr);
struct four_int64 verify_int_struct_int_pascal(int32_t a, struct four_int64 b, int32_t c);
struct four_int64 verify_int_struct_int_register(int32_t a, struct four_int64 b, int32_t c);
void verify_int_struct_int_callback_pascal(void *fn_ptr);
void verify_int_struct_int_callback_register(void *fn_ptr);
struct one_integer return_one_integer_struct_pascal();
struct one_integer return_one_integer_struct_register();
void verify_one_integer_struct_pascal(struct one_integer val);
void verify_one_integer_struct_register(struct one_integer val);
void verify_two_int_one_integer_struct_pascal(int32_t a, int32_t b, struct one_integer c);
void verify_two_int_one_integer_struct_register(int32_t a, int32_t b, struct one_integer c);
struct one_integer return_two_int_one_integer_struct_pascal(int32_t a, int32_t b, struct one_integer c);
struct one_integer return_two_int_one_integer_struct_register(int32_t a, int32_t b, struct one_integer c);
void verify_int_one_integer_int_pascal(int32_t a, struct one_integer b, int32_t c);
void verify_int_one_integer_int_register(int32_t a, struct one_integer b, int32_t c);
struct one_integer return_int_one_integer_int_pascal(int32_t a, struct one_integer b, int32_t c);
struct one_integer return_int_one_integer_int_register(int32_t a, struct one_integer b, int32_t c);
void verify_one_integer_callback_pascal(void *fn_ptr);
void verify_one_integer_callback_register(void *fn_ptr);
void verify_two_int_one_integer_callback_pascal(void *fn_ptr);
void verify_two_int_one_integer_callback_register(void *fn_ptr);
void verify_int_one_integer_int_callback_pascal(void *fn_ptr);
void verify_int_one_integer_int_callback_register(void *fn_ptr);
void mutate_large_struct_pascal(struct four_int64);
void mutate_large_struct_register(struct four_int64);

struct four_int64 get_struct() {
    struct four_int64 val;
    val.a = 0x5555555555555555;
    val.b = 0xAAAAAAAAAAAAAAAA;
    val.c = 0x6666666666666666;
    val.d = 0x9999999999999999;

    return val;
}

struct one_integer get_one_integer_struct() {
    struct one_integer val;
    val.value = 0x12345678;

    return val;
}

struct four_int64 native_identity_fn(struct four_int64 arg) {
    return arg;
}

void assert_equal(struct four_int64 a, struct four_int64 b) {
    assert(a.a == b.a);
    assert(a.b == b.b);
    assert(a.c == b.c);
    assert(a.d == b.d);
}

void assert_equal_one_integer(struct one_integer a, struct one_integer b) {
    assert(a.value == b.value);
}

void closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    *(struct four_int64 *)ret = *(struct four_int64 *)args[0];
}

void n_closure_handler(ffi_cif *cif, void *ret, void *args[], ffi_arg n) {
    for (int i = 0; i < n - 1; i++) {
        int32_t arg = *((int32_t *)args[i]);
        assert(arg == i);
    }

    *(struct four_int64 *)ret = *((struct four_int64 *)args[n-1]);
}

void int_struct_int_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert(*((int32_t *)args[0]) == 0);
    assert(*((int32_t *)args[2]) == 1);
    *(struct four_int64 *)ret = *(struct four_int64 *)args[1];
}

void one_integer_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    *(struct one_integer *)ret = *(struct one_integer *)args[0];
}

void two_int_one_integer_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert(*((int32_t *)args[0]) == 0);
    assert(*((int32_t *)args[1]) == 1);
    *(struct one_integer *)ret = *(struct one_integer *)args[2];
}

void int_one_integer_int_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert(*((int32_t *)args[0]) == 0);
    assert(*((int32_t *)args[2]) == 1);
    *(struct one_integer *)ret = *(struct one_integer *)args[1];
}


void test_callback(ffi_abi abi, void (*assert_callback)(void *)) {
    ffi_type test_struct_type = {0};
    ffi_type *type_elems[5];

    test_struct_type.type = FFI_TYPE_STRUCT;
    test_struct_type.elements = (ffi_type **) &type_elems;

    type_elems[0] = &ffi_type_uint64;
    type_elems[1] = &ffi_type_uint64;
    type_elems[2] = &ffi_type_uint64;
    type_elems[3] = &ffi_type_uint64;
    type_elems[4] = NULL;

    ffi_cif cif;
    ffi_type *arg_types[1];
    ffi_closure *closure;
    void *code;

    arg_types[0] = &test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, &test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, closure_handler, NULL, code) == FFI_OK);

    assert_callback(code);

    ffi_closure_free(closure);
}

void run_test_return_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    struct four_int64 result;

    assert(ffi_prep_cif(&cif, abi, 0, test_struct_type, NULL) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, NULL);

    assert_equal(result, get_struct());
}

void run_test_verify_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct four_int64 arg = get_struct();
    void *args[1];

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, &ffi_type_void, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, args);
}

void run_test_identity(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct four_int64 arg = get_struct();
    void *args[1];
    struct four_int64 result;

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal(result, get_struct());
}

void run_test_verify_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct four_int64 arg = get_struct();
    void *args[1];
    struct four_int64 result;

    ffi_closure *closure;
    void *closure_fn_ptr;

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);

    arg_types[0] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &closure_fn_ptr);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, closure_handler, NULL, closure_fn_ptr) == FFI_OK);

    fn_ptr(closure_fn_ptr);

    ffi_closure_free(closure);
}

void run_test_register_n_arguments(ffi_type *test_struct_type, unsigned int n, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[n];
    struct four_int64 arg = get_struct();
    void *args[n];
    int32_t actual_args[n-1];
    struct four_int64 result;

    for (int i = 0; i < n - 1; i++) {
        arg_types[i] = &ffi_type_sint32;
        actual_args[i] = i;
        args[i] = &actual_args[i];
    }

    arg_types[n-1] = test_struct_type;
    args[n-1] = &arg;

    assert(ffi_prep_cif(&cif, FFI_REGISTER, n, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal(result, get_struct());
}

void run_test_register_n_arguments_callback(ffi_type *test_struct_type, unsigned int n, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[n];

    ffi_closure *closure;
    void *closure_fn_ptr;
    void *code;

    for (int i = 0; i < n - 1; i++) {
        arg_types[i] = &ffi_type_sint32;
    }

    arg_types[n-1] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(ffi_prep_cif(&cif, FFI_REGISTER, n, test_struct_type, arg_types) == FFI_OK);
    assert(closure != NULL);

    assert(ffi_prep_closure_loc(closure, &cif, (void *)n_closure_handler, (void *)n, code) == FFI_OK);

    fn_ptr(code);
}

void run_test_int_struct_int(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[3];
    struct four_int64 arg = get_struct();
    int32_t actual_args[2];
    void *args[3];
    struct four_int64 result;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = test_struct_type;
    arg_types[2] = &ffi_type_sint32;

    actual_args[0] = 0;
    actual_args[1] = 1;
    args[0] = &actual_args[0];
    args[1] = &arg;
    args[2] = &actual_args[1];

    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal(result, get_struct());
}

void run_test_int_struct_int_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[3];

    ffi_closure *closure;
    void *closure_fn_ptr;
    void *code;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = test_struct_type;
    arg_types[2] = &ffi_type_sint32;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    assert(closure != NULL);

    assert(ffi_prep_closure_loc(closure, &cif, (void *)int_struct_int_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);
}

void run_test_return_one_integer_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    struct one_integer result;

    assert(ffi_prep_cif(&cif, abi, 0, test_struct_type, NULL) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, NULL);

    assert_equal_one_integer(result, get_one_integer_struct());
}

void run_test_verify_one_integer_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct one_integer arg = get_one_integer_struct();
    void *args[1];

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, &ffi_type_void, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, args);
}

void run_test_verify_two_int_one_integer_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[3];
    int32_t actual_args[2];
    struct one_integer arg = get_one_integer_struct();
    void *args[3];

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = &ffi_type_sint32;
    arg_types[2] = test_struct_type;

    actual_args[0] = 0;
    actual_args[1] = 1;
    args[0] = &actual_args[0];
    args[1] = &actual_args[1];
    args[2] = &arg;

    assert(ffi_prep_cif(&cif, abi, 3, &ffi_type_void, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, args);
}

void run_test_return_two_int_one_integer_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[3];
    int32_t actual_args[2];
    struct one_integer arg = get_one_integer_struct();
    struct one_integer result;
    void *args[3];

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = &ffi_type_sint32;
    arg_types[2] = test_struct_type;

    actual_args[0] = 0;
    actual_args[1] = 1;
    args[0] = &actual_args[0];
    args[1] = &actual_args[1];
    args[2] = &arg;

    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal_one_integer(result, get_one_integer_struct());
}

void run_test_verify_int_one_integer_int(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[3];
    int32_t actual_args[2];
    struct one_integer arg = get_one_integer_struct();
    void *args[3];

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = test_struct_type;
    arg_types[2] = &ffi_type_sint32;

    actual_args[0] = 0;
    actual_args[1] = 1;
    args[0] = &actual_args[0];
    args[1] = &arg;
    args[2] = &actual_args[1];

    assert(ffi_prep_cif(&cif, abi, 3, &ffi_type_void, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, args);
}

void run_test_return_int_one_integer_int(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[3];
    int32_t actual_args[2];
    struct one_integer arg = get_one_integer_struct();
    struct one_integer result;
    void *args[3];

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = test_struct_type;
    arg_types[2] = &ffi_type_sint32;

    actual_args[0] = 0;
    actual_args[1] = 1;
    args[0] = &actual_args[0];
    args[1] = &arg;
    args[2] = &actual_args[1];

    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal_one_integer(result, get_one_integer_struct());
}

void run_test_one_integer_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[1];

    ffi_closure *closure;
    void *code;

    arg_types[0] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, one_integer_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_two_int_one_integer_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[3];

    ffi_closure *closure;
    void *code;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = &ffi_type_sint32;
    arg_types[2] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, two_int_one_integer_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_int_one_integer_int_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[3];

    ffi_closure *closure;
    void *code;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = test_struct_type;
    arg_types[2] = &ffi_type_sint32;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 3, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, int_one_integer_int_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_return_struct_null_rvalue(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;

    assert(ffi_prep_cif(&cif, abi, 0, test_struct_type, NULL) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, NULL);
}

void run_test_mutate_large_struct(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct four_int64 arg = get_struct();
    void *args[1];

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, &ffi_type_void, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, NULL, args);

    assert_equal(arg, get_struct());
}

void run_test(char testcase) {
    ffi_type test_struct_type = {0};
    ffi_type *type_elems[5];
    ffi_type one_integer_struct_type = {0};
    ffi_type *one_integer_type_elems[2];

    struct four_int64 arg;
    struct four_int64 result;

    test_struct_type.type = FFI_TYPE_STRUCT;
    test_struct_type.elements = (ffi_type **) &type_elems;

    type_elems[0] = &ffi_type_uint64;
    type_elems[1] = &ffi_type_uint64;
    type_elems[2] = &ffi_type_uint64;
    type_elems[3] = &ffi_type_uint64;
    type_elems[4] = NULL;

    one_integer_struct_type.type = FFI_TYPE_STRUCT;
    one_integer_struct_type.elements = (ffi_type **) &one_integer_type_elems;

    one_integer_type_elems[0] = &ffi_type_sint32;
    one_integer_type_elems[1] = NULL;

    printf("Running test %c: ", testcase);

    switch(testcase) {
        case 'a':
            printf("return_struct_cdecl (native) ...\n");
            result = return_struct_cdecl();
            assert_equal(result, get_struct());
            break;
        case 'b':
            printf("return_struct_cdecl (libffi) ...\n");
            run_test_return_struct(&test_struct_type, FFI_DEFAULT_ABI, return_struct_cdecl);
            break;
        case 'c':
            printf("return_struct_pascal ...\n");
            run_test_return_struct(&test_struct_type, FFI_PASCAL, return_struct_pascal);
            break;
        case 'd':
            printf("return_struct_register ...\n");
            run_test_return_struct(&test_struct_type, FFI_REGISTER, return_struct_register);
            break;
        case 'e':
            printf("verify_struct_cdecl (native) ...\n");
            arg = get_struct();
            verify_struct_cdecl(arg);
            break;
        case 'f':
            printf("verify_struct_cdecl (libffi) ...\n");
            run_test_verify_struct(&test_struct_type, FFI_DEFAULT_ABI, verify_struct_cdecl);
            break;
        case 'g':
            printf("verify_struct_pascal ...\n");
            run_test_verify_struct(&test_struct_type, FFI_PASCAL, verify_struct_pascal);
            break;
        case 'h':
            printf("verify_struct_register ...\n");
            run_test_verify_struct(&test_struct_type, FFI_REGISTER, verify_struct_register);
            break;
        case 'i':
            printf("identity_cdecl (native) ...\n");
            arg = get_struct();
            result = identity_cdecl(arg);
            assert_equal(arg, result);
            break;
        case 'j':
            printf("identity_cdecl (libffi) ...\n");
            run_test_identity(&test_struct_type, FFI_DEFAULT_ABI, identity_cdecl);
            break;
        case 'k':
            printf("identity_pascal ...\n");
            run_test_identity(&test_struct_type, FFI_PASCAL, identity_pascal);
            break;
        case 'l':
            printf("identity_register ...\n");
            run_test_identity(&test_struct_type, FFI_REGISTER, identity_register);
            break;
        case 'm':
            printf("verify_callback_cdecl (native) ...\n");
            verify_callback_cdecl(native_identity_fn);
            break;
        case 'n':
            printf("verify_callback_cdecl (libffi) ...\n");
            run_test_verify_callback(&test_struct_type, FFI_DEFAULT_ABI, verify_callback_cdecl);
            break;
        case 'o':
            printf("verify_callback_pascal ...\n");
            run_test_verify_callback(&test_struct_type, FFI_PASCAL, verify_callback_pascal);
            break;
        case 'p':
            printf("verify_callback_register ...\n");
            run_test_verify_callback(&test_struct_type, FFI_REGISTER, verify_callback_register);
            break;
        case 'q':
            printf("register_two_args_return_struct ...\n");
            run_test_register_n_arguments(&test_struct_type, 2, register_two_args_return_struct);
            break;
        case 'r':
            printf("register_three_args_return_struct ...\n");
            run_test_register_n_arguments(&test_struct_type, 3, register_three_args_return_struct);
            break;
        case 's':
            printf("register_four_args_return_struct ...\n");
            run_test_register_n_arguments(&test_struct_type, 4, register_four_args_return_struct);
            break;
        case 't':
            printf("verify_two_args_callback_register ...\n");
            run_test_register_n_arguments_callback(&test_struct_type, 2, verify_two_args_callback_register);
            break;
        case 'u':
            printf("verify_three_args_callback_register ...\n");
            run_test_register_n_arguments_callback(&test_struct_type, 3, verify_three_args_callback_register);
            break;
        case 'v':
            printf("verify_four_args_callback_register ...\n");
            run_test_register_n_arguments_callback(&test_struct_type, 4, verify_four_args_callback_register);
            break;
        case 'w':
            printf("verify_int_struct_int_pascal ...\n");
            run_test_int_struct_int(&test_struct_type, FFI_PASCAL, verify_int_struct_int_pascal);
            break;
        case 'x':
            printf("verify_int_struct_int_register ...\n");
            run_test_int_struct_int(&test_struct_type, FFI_REGISTER, verify_int_struct_int_register);
            break;
        case 'y':
            printf("verify_int_struct_int_callback_pascal ...\n");
            run_test_int_struct_int_callback(&test_struct_type, FFI_PASCAL, verify_int_struct_int_callback_pascal);
            break;
        case 'z':
            printf("verify_int_struct_int_callback_register ...\n");
            run_test_int_struct_int_callback(&test_struct_type, FFI_REGISTER, verify_int_struct_int_callback_register);
            break;
        case 'A':
            printf("return_one_integer_struct_pascal ...\n");
            run_test_return_one_integer_struct(&one_integer_struct_type, FFI_PASCAL, return_one_integer_struct_pascal);
            break;
        case 'B':
            printf("return_one_integer_struct_register ...\n");
            run_test_return_one_integer_struct(&one_integer_struct_type, FFI_REGISTER, return_one_integer_struct_register);
            break;
        case 'C':
            printf("verify_one_integer_struct_pascal ...\n");
            run_test_verify_one_integer_struct(&one_integer_struct_type, FFI_PASCAL, verify_one_integer_struct_pascal);
            break;
        case 'D':
            printf("verify_one_integer_struct_register ...\n");
            run_test_verify_one_integer_struct(&one_integer_struct_type, FFI_REGISTER, verify_one_integer_struct_register);
            break;
        case 'E':
            printf("verify_two_int_one_integer_struct_pascal ...\n");
            run_test_verify_two_int_one_integer_struct(&one_integer_struct_type, FFI_PASCAL, verify_two_int_one_integer_struct_pascal);
            break;
        case 'F':
            printf("verify_two_int_one_integer_struct_register ...\n");
            run_test_verify_two_int_one_integer_struct(&one_integer_struct_type, FFI_REGISTER, verify_two_int_one_integer_struct_register);
            break;
        case 'G':
            printf("return_two_int_one_integer_struct_pascal ...\n");
            run_test_return_two_int_one_integer_struct(&one_integer_struct_type, FFI_PASCAL, return_two_int_one_integer_struct_pascal);
            break;
        case 'H':
            printf("return_two_int_one_integer_struct_register ...\n");
            run_test_return_two_int_one_integer_struct(&one_integer_struct_type, FFI_REGISTER, return_two_int_one_integer_struct_register);
            break;
        case 'I':
            printf("verify_int_one_integer_int_pascal ...\n");
            run_test_verify_int_one_integer_int(&one_integer_struct_type, FFI_PASCAL, verify_int_one_integer_int_pascal);
            break;
        case 'J':
            printf("verify_int_one_integer_int_register ...\n");
            run_test_verify_int_one_integer_int(&one_integer_struct_type, FFI_REGISTER, verify_int_one_integer_int_register);
            break;
        case 'K':
            printf("return_int_one_integer_int_pascal ...\n");
            run_test_return_int_one_integer_int(&one_integer_struct_type, FFI_PASCAL, return_int_one_integer_int_pascal);
            break;
        case 'L':
            printf("return_int_one_integer_int_register ...\n");
            run_test_return_int_one_integer_int(&one_integer_struct_type, FFI_REGISTER, return_int_one_integer_int_register);
            break;
        case 'M':
            printf("verify_one_integer_callback_pascal ...\n");
            run_test_one_integer_callback(&one_integer_struct_type, FFI_PASCAL, verify_one_integer_callback_pascal);
            break;
        case 'N':
            printf("verify_one_integer_callback_register ...\n");
            run_test_one_integer_callback(&one_integer_struct_type, FFI_REGISTER, verify_one_integer_callback_register);
            break;
        case 'O':
            printf("verify_two_int_one_integer_callback_pascal ...\n");
            run_test_two_int_one_integer_callback(&one_integer_struct_type, FFI_PASCAL, verify_two_int_one_integer_callback_pascal);
            break;
        case 'P':
            printf("verify_two_int_one_integer_callback_register ...\n");
            run_test_two_int_one_integer_callback(&one_integer_struct_type, FFI_REGISTER, verify_two_int_one_integer_callback_register);
            break;
        case 'Q':
            printf("verify_int_one_integer_int_callback_pascal ...\n");
            run_test_int_one_integer_int_callback(&one_integer_struct_type, FFI_PASCAL, verify_int_one_integer_int_callback_pascal);
            break;
        case 'R':
            printf("verify_int_one_integer_int_callback_register ...\n");
            run_test_int_one_integer_int_callback(&one_integer_struct_type, FFI_REGISTER, verify_int_one_integer_int_callback_register);
            break;
        case 'S':
            printf("return_struct_pascal (NULL rvalue) ...\n");
            run_test_return_struct_null_rvalue(&test_struct_type, FFI_PASCAL, return_struct_pascal);
            break;
        case 'T':
            printf("return_struct_register (NULL rvalue) ...\n");
            run_test_return_struct_null_rvalue(&test_struct_type, FFI_REGISTER, return_struct_register);
            break;
        case 'U':
            printf("mutate_large_struct_pascal ...\n");
            run_test_mutate_large_struct(&test_struct_type, FFI_PASCAL, mutate_large_struct_pascal);
            break;
        case 'V':
            printf("mutate_large_struct_register ...\n");
            run_test_mutate_large_struct(&test_struct_type, FFI_REGISTER, mutate_large_struct_register);
            break;
        default:
            printf("ERROR! Unknown test case, aborting.\n");
            exit(1);
    }
    printf("\tOK!\n");
}

int main(int argc, char **argv) {
    if (argc > 1) {
        run_test(*(argv[1]));
        return 0;
    }

    for (char a = 'a'; a <= 'z'; a++) {
        run_test(a);
    }
    for (char a = 'A'; a <= 'V'; a++) {
        run_test(a);
    }

    return 0;
}
