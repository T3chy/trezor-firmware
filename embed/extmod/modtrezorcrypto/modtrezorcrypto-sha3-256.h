/*
 * Copyright (c) Pavol Rusnak, SatoshiLabs
 *
 * Licensed under TREZOR License
 * see LICENSE file for details
 */

#include "py/objstr.h"

#include "sha3.h"

/// class Sha3_256:
///     '''
///     SHA3_256 context.
///     '''
typedef struct _mp_obj_Sha3_256_t {
    mp_obj_base_t base;
    SHA3_CTX ctx;
} mp_obj_Sha3_256_t;

STATIC mp_obj_t mod_trezorcrypto_Sha3_256_update(mp_obj_t self, mp_obj_t data);

/// def __init__(self, data: bytes = None) -> None:
///     '''
///     Creates a hash context object.
///     '''
STATIC mp_obj_t mod_trezorcrypto_Sha3_256_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    mp_obj_Sha3_256_t *o = m_new_obj(mp_obj_Sha3_256_t);
    o->base.type = type;
    sha3_256_Init(&(o->ctx));
    // constructor called with bytes/str as first parameter
    if (n_args == 1) {
        mod_trezorcrypto_Sha3_256_update(MP_OBJ_FROM_PTR(o), args[0]);
    }
    return MP_OBJ_FROM_PTR(o);
}

/// def update(self, data: bytes) -> None:
///     '''
///     Update the hash context with hashed data.
///     '''
STATIC mp_obj_t mod_trezorcrypto_Sha3_256_update(mp_obj_t self, mp_obj_t data) {
    mp_obj_Sha3_256_t *o = MP_OBJ_TO_PTR(self);
    mp_buffer_info_t msg;
    mp_get_buffer_raise(data, &msg, MP_BUFFER_READ);
    if (msg.len > 0) {
        sha3_Update(&(o->ctx), msg.buf, msg.len);
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_trezorcrypto_Sha3_256_update_obj, mod_trezorcrypto_Sha3_256_update);

/// def digest(self, keccak: bool = False) -> bytes:
///     '''
///     Returns the digest of hashed data.
///     '''
STATIC mp_obj_t mod_trezorcrypto_Sha3_256_digest(size_t n_args, const mp_obj_t *args) {
    mp_obj_Sha3_256_t *o = MP_OBJ_TO_PTR(args[0]);
    uint8_t out[SHA3_256_DIGEST_LENGTH];
    SHA3_CTX ctx;
    memcpy(&ctx, &(o->ctx), sizeof(SHA3_CTX));
    if (n_args > 1 && args[1] == mp_const_true) {
        keccak_Final(&ctx, out);
    } else {
        sha3_Final(&ctx, out);
    }
    memset(&ctx, 0, sizeof(SHA3_CTX));
    return mp_obj_new_bytes(out, sizeof(out));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mod_trezorcrypto_Sha3_256_digest_obj, 1, 2, mod_trezorcrypto_Sha3_256_digest);

STATIC mp_obj_t mod_trezorcrypto_Sha3_256___del__(mp_obj_t self) {
    mp_obj_Sha3_256_t *o = MP_OBJ_TO_PTR(self);
    memset(&(o->ctx), 0, sizeof(SHA3_CTX));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_trezorcrypto_Sha3_256___del___obj, mod_trezorcrypto_Sha3_256___del__);

STATIC const mp_rom_map_elem_t mod_trezorcrypto_Sha3_256_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&mod_trezorcrypto_Sha3_256_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_digest), MP_ROM_PTR(&mod_trezorcrypto_Sha3_256_digest_obj) },
    { MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&mod_trezorcrypto_Sha3_256___del___obj) },
    { MP_ROM_QSTR(MP_QSTR_block_size), MP_OBJ_NEW_SMALL_INT(SHA3_256_BLOCK_LENGTH) },
    { MP_ROM_QSTR(MP_QSTR_digest_size), MP_OBJ_NEW_SMALL_INT(SHA3_256_DIGEST_LENGTH) },
};
STATIC MP_DEFINE_CONST_DICT(mod_trezorcrypto_Sha3_256_locals_dict, mod_trezorcrypto_Sha3_256_locals_dict_table);

STATIC const mp_obj_type_t mod_trezorcrypto_Sha3_256_type = {
    { &mp_type_type },
    .name = MP_QSTR_Sha3_256,
    .make_new = mod_trezorcrypto_Sha3_256_make_new,
    .locals_dict = (void*)&mod_trezorcrypto_Sha3_256_locals_dict,
};
