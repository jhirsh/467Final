// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <string.h>
#include "occupancy_grid_t.h"

static int __occupancy_grid_t_hash_computed;
static int64_t __occupancy_grid_t_hash;

int64_t __occupancy_grid_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __occupancy_grid_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = (void*)__occupancy_grid_t_get_hash;
    (void) cp;

    int64_t hash = (int64_t)0x6aa23f24a5336649LL
         + __int64_t_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __float_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int8_t_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __occupancy_grid_t_get_hash(void)
{
    if (!__occupancy_grid_t_hash_computed) {
        __occupancy_grid_t_hash = __occupancy_grid_t_hash_recursive(NULL);
        __occupancy_grid_t_hash_computed = 1;
    }

    return __occupancy_grid_t_hash;
}

int __occupancy_grid_t_encode_array(void *buf, int offset, int maxlen, const occupancy_grid_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].utime), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].origin_x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].origin_y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_encode_array(buf, offset + pos, maxlen - pos, &(p[element].meters_per_cell), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].width), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].height), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].num_cells), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, p[element].cells, p[element].num_cells);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int occupancy_grid_t_encode(void *buf, int offset, int maxlen, const occupancy_grid_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __occupancy_grid_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __occupancy_grid_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __occupancy_grid_t_encoded_array_size(const occupancy_grid_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int64_t_encoded_array_size(&(p[element].utime), 1);

        size += __float_encoded_array_size(&(p[element].origin_x), 1);

        size += __float_encoded_array_size(&(p[element].origin_y), 1);

        size += __float_encoded_array_size(&(p[element].meters_per_cell), 1);

        size += __int32_t_encoded_array_size(&(p[element].width), 1);

        size += __int32_t_encoded_array_size(&(p[element].height), 1);

        size += __int32_t_encoded_array_size(&(p[element].num_cells), 1);

        size += __int8_t_encoded_array_size(p[element].cells, p[element].num_cells);

    }
    return size;
}

int occupancy_grid_t_encoded_size(const occupancy_grid_t *p)
{
    return 8 + __occupancy_grid_t_encoded_array_size(p, 1);
}

size_t occupancy_grid_t_struct_size(void)
{
    return sizeof(occupancy_grid_t);
}

int occupancy_grid_t_num_fields(void)
{
    return 8;
}

int occupancy_grid_t_get_field(const occupancy_grid_t *p, int i, lcm_field_t *f)
{
    if (0 > i || i >= occupancy_grid_t_num_fields())
        return 1;
    
    switch (i) {
    
        case 0: {
            f->name = "utime";
            f->type = LCM_FIELD_INT64_T;
            f->typestr = "int64_t";
            f->num_dim = 0;
            f->data = (void *) &p->utime;
            return 0;
        }
        
        case 1: {
            f->name = "origin_x";
            f->type = LCM_FIELD_FLOAT;
            f->typestr = "float";
            f->num_dim = 0;
            f->data = (void *) &p->origin_x;
            return 0;
        }
        
        case 2: {
            f->name = "origin_y";
            f->type = LCM_FIELD_FLOAT;
            f->typestr = "float";
            f->num_dim = 0;
            f->data = (void *) &p->origin_y;
            return 0;
        }
        
        case 3: {
            f->name = "meters_per_cell";
            f->type = LCM_FIELD_FLOAT;
            f->typestr = "float";
            f->num_dim = 0;
            f->data = (void *) &p->meters_per_cell;
            return 0;
        }
        
        case 4: {
            f->name = "width";
            f->type = LCM_FIELD_INT32_T;
            f->typestr = "int32_t";
            f->num_dim = 0;
            f->data = (void *) &p->width;
            return 0;
        }
        
        case 5: {
            f->name = "height";
            f->type = LCM_FIELD_INT32_T;
            f->typestr = "int32_t";
            f->num_dim = 0;
            f->data = (void *) &p->height;
            return 0;
        }
        
        case 6: {
            f->name = "num_cells";
            f->type = LCM_FIELD_INT32_T;
            f->typestr = "int32_t";
            f->num_dim = 0;
            f->data = (void *) &p->num_cells;
            return 0;
        }
        
        case 7: {
            f->name = "cells";
            f->type = LCM_FIELD_INT8_T;
            f->typestr = "int8_t";
            f->num_dim = 1;
            f->dim_size[0] = p->num_cells;
            f->dim_is_variable[0] = 1;
            f->data = (void *) &p->cells;
            return 0;
        }
        
        default:
            return 1;
    }
}

const lcm_type_info_t *occupancy_grid_t_get_type_info(void)
{
    static int init = 0;
    static lcm_type_info_t typeinfo;
    if (!init) {
        typeinfo.encode         = (lcm_encode_t) occupancy_grid_t_encode;
        typeinfo.decode         = (lcm_decode_t) occupancy_grid_t_decode;
        typeinfo.decode_cleanup = (lcm_decode_cleanup_t) occupancy_grid_t_decode_cleanup;
        typeinfo.encoded_size   = (lcm_encoded_size_t) occupancy_grid_t_encoded_size;
        typeinfo.struct_size    = (lcm_struct_size_t)  occupancy_grid_t_struct_size;
        typeinfo.num_fields     = (lcm_num_fields_t) occupancy_grid_t_num_fields;
        typeinfo.get_field      = (lcm_get_field_t) occupancy_grid_t_get_field;
        typeinfo.get_hash       = (lcm_get_hash_t) __occupancy_grid_t_get_hash;
    }
    
    return &typeinfo;
}
int __occupancy_grid_t_decode_array(const void *buf, int offset, int maxlen, occupancy_grid_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].utime), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].origin_x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].origin_y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __float_decode_array(buf, offset + pos, maxlen - pos, &(p[element].meters_per_cell), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].width), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].height), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].num_cells), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        p[element].cells = (int8_t*) lcm_malloc(sizeof(int8_t) * p[element].num_cells);
        thislen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, p[element].cells, p[element].num_cells);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __occupancy_grid_t_decode_array_cleanup(occupancy_grid_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_decode_array_cleanup(&(p[element].utime), 1);

        __float_decode_array_cleanup(&(p[element].origin_x), 1);

        __float_decode_array_cleanup(&(p[element].origin_y), 1);

        __float_decode_array_cleanup(&(p[element].meters_per_cell), 1);

        __int32_t_decode_array_cleanup(&(p[element].width), 1);

        __int32_t_decode_array_cleanup(&(p[element].height), 1);

        __int32_t_decode_array_cleanup(&(p[element].num_cells), 1);

        __int8_t_decode_array_cleanup(p[element].cells, p[element].num_cells);
        if (p[element].cells) free(p[element].cells);

    }
    return 0;
}

int occupancy_grid_t_decode(const void *buf, int offset, int maxlen, occupancy_grid_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __occupancy_grid_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __occupancy_grid_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int occupancy_grid_t_decode_cleanup(occupancy_grid_t *p)
{
    return __occupancy_grid_t_decode_array_cleanup(p, 1);
}

int __occupancy_grid_t_clone_array(const occupancy_grid_t *p, occupancy_grid_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_clone_array(&(p[element].utime), &(q[element].utime), 1);

        __float_clone_array(&(p[element].origin_x), &(q[element].origin_x), 1);

        __float_clone_array(&(p[element].origin_y), &(q[element].origin_y), 1);

        __float_clone_array(&(p[element].meters_per_cell), &(q[element].meters_per_cell), 1);

        __int32_t_clone_array(&(p[element].width), &(q[element].width), 1);

        __int32_t_clone_array(&(p[element].height), &(q[element].height), 1);

        __int32_t_clone_array(&(p[element].num_cells), &(q[element].num_cells), 1);

        q[element].cells = (int8_t*) lcm_malloc(sizeof(int8_t) * q[element].num_cells);
        __int8_t_clone_array(p[element].cells, q[element].cells, p[element].num_cells);

    }
    return 0;
}

occupancy_grid_t *occupancy_grid_t_copy(const occupancy_grid_t *p)
{
    occupancy_grid_t *q = (occupancy_grid_t*) malloc(sizeof(occupancy_grid_t));
    __occupancy_grid_t_clone_array(p, q, 1);
    return q;
}

void occupancy_grid_t_destroy(occupancy_grid_t *p)
{
    __occupancy_grid_t_decode_array_cleanup(p, 1);
    free(p);
}

int occupancy_grid_t_publish(lcm_t *lc, const char *channel, const occupancy_grid_t *p)
{
      int max_data_size = occupancy_grid_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = occupancy_grid_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _occupancy_grid_t_subscription_t {
    occupancy_grid_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void occupancy_grid_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    occupancy_grid_t p;
    memset(&p, 0, sizeof(occupancy_grid_t));
    status = occupancy_grid_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding occupancy_grid_t!!!\n", status);
        return;
    }

    occupancy_grid_t_subscription_t *h = (occupancy_grid_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    occupancy_grid_t_decode_cleanup (&p);
}

occupancy_grid_t_subscription_t* occupancy_grid_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    occupancy_grid_t_handler_t f, void *userdata)
{
    occupancy_grid_t_subscription_t *n = (occupancy_grid_t_subscription_t*)
                       malloc(sizeof(occupancy_grid_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 occupancy_grid_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg occupancy_grid_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int occupancy_grid_t_subscription_set_queue_capacity (occupancy_grid_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int occupancy_grid_t_unsubscribe(lcm_t *lcm, occupancy_grid_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe occupancy_grid_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

