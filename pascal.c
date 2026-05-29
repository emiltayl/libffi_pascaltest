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

struct four_byte_record {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
};

struct five_byte_record {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
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
struct four_byte_record identity_four_byte_struct_pascal(struct four_byte_record value);
struct four_byte_record identity_four_byte_struct_register(struct four_byte_record value);
struct five_byte_record identity_five_byte_struct_pascal(struct five_byte_record value);
struct five_byte_record identity_five_byte_struct_register(struct five_byte_record value);
void verify_four_byte_callback_pascal(void *fn_ptr);
void verify_four_byte_callback_register(void *fn_ptr);
void verify_five_byte_callback_pascal(void *fn_ptr);
void verify_five_byte_callback_register(void *fn_ptr);
void verify_int_callback_pascal(void *fn_ptr);
void verify_four_int_callback_register(void *fn_ptr);
void mutate_large_struct_pascal(struct four_int64);
void mutate_large_struct_register(struct four_int64);
void verify_integer_sizes_register(int8_t a, int16_t b, int32_t c, int64_t d, struct four_int64 e);
int32_t verify_mixed_alignment_pascal(int8_t a, int16_t b, int32_t c, int64_t d, float e, double f);
int32_t verify_mixed_alignment_register(int8_t a, int16_t b, int32_t c, int64_t d, float e, double f);
void verify_mixed_alignment_callback_pascal(void *fn_ptr);
void verify_mixed_alignment_callback_register(void *fn_ptr);

#define MIXED_ALIGNMENT_NARGS 6
#define MIXED_ALIGNMENT_INT8 ((int8_t)0x12)
#define MIXED_ALIGNMENT_INT16 ((int16_t)0x3456)
#define MIXED_ALIGNMENT_INT32 ((int32_t)0x12345678)
#define MIXED_ALIGNMENT_INT64 INT64_C(0x1122334455667788)
#define MIXED_ALIGNMENT_FLOAT 16.25f
#define MIXED_ALIGNMENT_DOUBLE 1024.5
#define MIXED_ALIGNMENT_RESULT ((int32_t)0x13572468)

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

struct four_byte_record get_four_byte_record() {
    struct four_byte_record val;

    assert(sizeof(struct four_byte_record) == 4);

    val.a = '0';
    val.b = '1';
    val.c = '2';
    val.d = '3';

    return val;
}

struct five_byte_record get_five_byte_record() {
    struct five_byte_record val;

    assert(sizeof(struct five_byte_record) == 5);

    val.a = '0';
    val.b = '1';
    val.c = '2';
    val.d = '3';
    val.e = '4';

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

void assert_equal_four_byte_record(struct four_byte_record a, struct four_byte_record b) {
    assert(a.a == b.a);
    assert(a.b == b.b);
    assert(a.c == b.c);
    assert(a.d == b.d);
}

void assert_equal_five_byte_record(struct five_byte_record a, struct five_byte_record b) {
    assert(a.a == b.a);
    assert(a.b == b.b);
    assert(a.c == b.c);
    assert(a.d == b.d);
    assert(a.e == b.e);
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

void four_byte_record_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    *(struct four_byte_record *)ret = *(struct four_byte_record *)args[0];
}

void five_byte_record_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    *(struct five_byte_record *)ret = *(struct five_byte_record *)args[0];
}

void int_pascal_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert(*((int32_t *)args[0]) == 41);
    *(int32_t *)ret = 42;
}

void four_int_register_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert(*((int32_t *)args[0]) == 0);
    assert(*((int32_t *)args[1]) == 1);
    assert(*((int32_t *)args[2]) == 2);
    assert(*((int32_t *)args[3]) == 3);
    *(int32_t *)ret = 6;
}

void assert_mixed_alignment_values(int8_t a, int16_t b, int32_t c, int64_t d, float e, double f) {
    assert(a == MIXED_ALIGNMENT_INT8);
    assert(b == MIXED_ALIGNMENT_INT16);
    assert(c == MIXED_ALIGNMENT_INT32);
    assert(d == MIXED_ALIGNMENT_INT64);
    assert(e == MIXED_ALIGNMENT_FLOAT);
    assert(f == MIXED_ALIGNMENT_DOUBLE);
}

void mixed_alignment_closure_handler(ffi_cif *cif, void *ret, void *args[], void *data) {
    assert_mixed_alignment_values(
        *((int8_t *)args[0]),
        *((int16_t *)args[1]),
        *((int32_t *)args[2]),
        *((int64_t *)args[3]),
        *((float *)args[4]),
        *((double *)args[5]));
    *(int32_t *)ret = MIXED_ALIGNMENT_RESULT;
}

void init_mixed_alignment_arg_types(ffi_type *arg_types[MIXED_ALIGNMENT_NARGS]) {
    arg_types[0] = &ffi_type_sint8;
    arg_types[1] = &ffi_type_sint16;
    arg_types[2] = &ffi_type_sint32;
    arg_types[3] = &ffi_type_sint64;
    arg_types[4] = &ffi_type_float;
    arg_types[5] = &ffi_type_double;
}

void init_mixed_alignment_args(
    void *args[MIXED_ALIGNMENT_NARGS],
    int8_t *a,
    int16_t *b,
    int32_t *c,
    int64_t *d,
    float *e,
    double *f)
{
    *a = MIXED_ALIGNMENT_INT8;
    *b = MIXED_ALIGNMENT_INT16;
    *c = MIXED_ALIGNMENT_INT32;
    *d = MIXED_ALIGNMENT_INT64;
    *e = MIXED_ALIGNMENT_FLOAT;
    *f = MIXED_ALIGNMENT_DOUBLE;

    args[0] = a;
    args[1] = b;
    args[2] = c;
    args[3] = d;
    args[4] = e;
    args[5] = f;
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

void run_test_four_byte_record_identity(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct four_byte_record arg = get_four_byte_record();
    struct four_byte_record result;
    void *args[1];

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal_four_byte_record(result, get_four_byte_record());
}

void run_test_five_byte_record_identity(ffi_type *test_struct_type, ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    struct five_byte_record arg = get_five_byte_record();
    struct five_byte_record result;
    void *args[1];

    arg_types[0] = test_struct_type;
    args[0] = &arg;

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert_equal_five_byte_record(result, get_five_byte_record());
}

void run_test_four_byte_record_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[1];

    ffi_closure *closure;
    void *code;

    arg_types[0] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, four_byte_record_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_five_byte_record_callback(ffi_type *test_struct_type, ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[1];

    ffi_closure *closure;
    void *code;

    arg_types[0] = test_struct_type;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, five_byte_record_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_int_callback_pascal(void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[1];

    ffi_closure *closure;
    void *code;

    arg_types[0] = &ffi_type_sint32;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, FFI_PASCAL, 1, &ffi_type_sint32, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, int_pascal_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_four_int_callback_register(void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[4];

    ffi_closure *closure;
    void *code;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = &ffi_type_sint32;
    arg_types[2] = &ffi_type_sint32;
    arg_types[3] = &ffi_type_sint32;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, FFI_REGISTER, 4, &ffi_type_sint32, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, four_int_register_closure_handler, NULL, code) == FFI_OK);

    fn_ptr(code);

    ffi_closure_free(closure);
}

void run_test_mixed_alignment(ffi_abi abi, void *fn_ptr) {
    ffi_cif cif;
    ffi_type *arg_types[MIXED_ALIGNMENT_NARGS];
    void *args[MIXED_ALIGNMENT_NARGS];
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
    float e;
    double f;
    int32_t result;

    init_mixed_alignment_arg_types(arg_types);
    init_mixed_alignment_args(args, &a, &b, &c, &d, &e, &f);

    assert(ffi_prep_cif(&cif, abi, MIXED_ALIGNMENT_NARGS, &ffi_type_sint32, arg_types) == FFI_OK);
    ffi_call(&cif, fn_ptr, &result, args);

    assert(result == MIXED_ALIGNMENT_RESULT);
}

void run_test_mixed_alignment_callback(ffi_abi abi, void (*fn_ptr)(void *)) {
    ffi_cif cif;
    ffi_type *arg_types[MIXED_ALIGNMENT_NARGS];
    ffi_closure *closure;
    void *code;

    init_mixed_alignment_arg_types(arg_types);

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, MIXED_ALIGNMENT_NARGS, &ffi_type_sint32, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, mixed_alignment_closure_handler, NULL, code) == FFI_OK);

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

void test_ffi_call_closure(ffi_type *test_struct_type, ffi_abi abi) {
    ffi_cif cif;
    ffi_type *arg_types[1];
    void *args[1];
    ffi_closure *closure;
    void *code;
    struct four_int64 struct_arg = get_struct();
    struct four_int64 result;

    arg_types[0] = test_struct_type;
    args[0] = &struct_arg;

    closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    assert(closure != NULL);

    assert(ffi_prep_cif(&cif, abi, 1, test_struct_type, arg_types) == FFI_OK);
    assert(ffi_prep_closure_loc(closure, &cif, closure_handler, NULL, code) == FFI_OK);

    ffi_call(&cif, code, &result, args);

    assert_equal(struct_arg, result);

    ffi_closure_free(closure);
}

void run_test(char testcase) {
    ffi_type test_struct_type = {0};
    ffi_type *type_elems[5];
    ffi_type one_integer_struct_type = {0};
    ffi_type *one_integer_type_elems[2];
    ffi_type four_byte_record_type = {0};
    ffi_type *four_byte_record_type_elems[5];
    ffi_type five_byte_record_type = {0};
    ffi_type *five_byte_record_type_elems[6];

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

    four_byte_record_type.type = FFI_TYPE_STRUCT;
    four_byte_record_type.elements = (ffi_type **) &four_byte_record_type_elems;

    four_byte_record_type_elems[0] = &ffi_type_uint8;
    four_byte_record_type_elems[1] = &ffi_type_uint8;
    four_byte_record_type_elems[2] = &ffi_type_uint8;
    four_byte_record_type_elems[3] = &ffi_type_uint8;
    four_byte_record_type_elems[4] = NULL;

    five_byte_record_type.type = FFI_TYPE_STRUCT;
    five_byte_record_type.elements = (ffi_type **) &five_byte_record_type_elems;

    five_byte_record_type_elems[0] = &ffi_type_uint8;
    five_byte_record_type_elems[1] = &ffi_type_uint8;
    five_byte_record_type_elems[2] = &ffi_type_uint8;
    five_byte_record_type_elems[3] = &ffi_type_uint8;
    five_byte_record_type_elems[4] = &ffi_type_uint8;
    five_byte_record_type_elems[5] = NULL;

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
        case 'W':
            printf("test_ffi_call_closure_pascal ...\n");
            test_ffi_call_closure(&test_struct_type, FFI_PASCAL);
            break;
        case 'X':
            printf("test_ffi_call_closure_register ...\n");
            test_ffi_call_closure(&test_struct_type, FFI_REGISTER);
            break;
        case 'Y':
            printf("identity_four_byte_struct_pascal ...\n");
            run_test_four_byte_record_identity(&four_byte_record_type, FFI_PASCAL, identity_four_byte_struct_pascal);
            break;
        case 'Z':
            printf("identity_four_byte_struct_register ...\n");
            run_test_four_byte_record_identity(&four_byte_record_type, FFI_REGISTER, identity_four_byte_struct_register);
            break;
        case '0':
            printf("verify_four_byte_callback_pascal ...\n");
            run_test_four_byte_record_callback(&four_byte_record_type, FFI_PASCAL, verify_four_byte_callback_pascal);
            break;
        case '1':
            printf("verify_four_byte_callback_register ...\n");
            run_test_four_byte_record_callback(&four_byte_record_type, FFI_REGISTER, verify_four_byte_callback_register);
            break;
        case '2':
            printf("identity_five_byte_struct_pascal ...\n");
            run_test_five_byte_record_identity(&five_byte_record_type, FFI_PASCAL, identity_five_byte_struct_pascal);
            break;
        case '3':
            printf("identity_five_byte_struct_register ...\n");
            run_test_five_byte_record_identity(&five_byte_record_type, FFI_REGISTER, identity_five_byte_struct_register);
            break;
        case '4':
            printf("verify_five_byte_callback_pascal ...\n");
            run_test_five_byte_record_callback(&five_byte_record_type, FFI_PASCAL, verify_five_byte_callback_pascal);
            break;
        case '5':
            printf("verify_five_byte_callback_register ...\n");
            run_test_five_byte_record_callback(&five_byte_record_type, FFI_REGISTER, verify_five_byte_callback_register);
            break;
        case '6':
            printf("verify_int_callback_pascal ...\n");
            run_test_int_callback_pascal(verify_int_callback_pascal);
            break;
        case '7':
            printf("verify_four_int_callback_register ...\n");
            run_test_four_int_callback_register(verify_four_int_callback_register);
            break;
        case '8':
            printf("verify_mixed_alignment_pascal/register ...\n");
            run_test_mixed_alignment(FFI_PASCAL, verify_mixed_alignment_pascal);
            run_test_mixed_alignment(FFI_REGISTER, verify_mixed_alignment_register);
            break;
        case '9':
            printf("verify_mixed_alignment_callback_pascal/register ...\n");
            run_test_mixed_alignment_callback(FFI_PASCAL, verify_mixed_alignment_callback_pascal);
            run_test_mixed_alignment_callback(FFI_REGISTER, verify_mixed_alignment_callback_register);
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
    for (char a = 'A'; a <= 'Z'; a++) {
        run_test(a);
    }
    for (char a = '0'; a <= '9'; a++) {
        run_test(a);
    }

    return 0;
}
