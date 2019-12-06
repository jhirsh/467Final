// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <string.h>
#include "arm_path_t.h"

static int __arm_path_t_hash_computed;
static int64_t __arm_path_t_hash;

int64_t __arm_path_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __arm_path_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = (void*)__arm_path_t_get_hash;
    (void) cp;

    int64_t hash = (int64_t)0xb035843bfa4ee381LL
         + __int32_t_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __arm_path_t_get_hash(void)
{
    if (!__arm_path_t_hash_computed) {
        __arm_path_t_hash = __arm_path_t_hash_recursive(NULL);
        __arm_path_t_hash_computed = 1;
    }

    return __arm_path_t_hash;
}

int __arm_path_t_encode_array(void *buf, int offset, int maxlen, const arm_path_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].waypoints_num), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        { int a;
        for (a = 0; a < p[element].waypoints_num; a++) {
            thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].waypoints[a], 2);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, &(p[element].speed), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int arm_path_t_encode(void *buf, int offset, int maxlen, const arm_path_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __arm_path_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __arm_path_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __arm_path_t_encoded_array_size(const arm_path_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int32_t_encoded_array_size(&(p[element].waypoints_num), 1);

        { int a;
        for (a = 0; a < p[element].waypoints_num; a++) {
            size += __double_encoded_array_size(p[element].waypoints[a], 2);
        }
        }

        size += __double_encoded_array_size(&(p[element].speed), 1);

    }
    return size;
}

int arm_path_t_encoded_size(const arm_path_t *p)
{
    return 8 + __arm_path_t_encoded_array_size(p, 1);
}

size_t arm_path_t_struct_size(void)
{
    return sizeof(arm_path_t);
}

int arm_path_t_num_fields(void)
{
    return 3;
}

int arm_path_t_get_field(const arm_path_t *p, int i, lcm_field_t *f)
{
    if (0 > i || i >= arm_path_t_num_fields())
        return 1;
    
    switch (i) {
    
        case 0: {
            f->name = "waypoints_num";
            f->type = LCM_FIELD_INT32_T;
            f->typestr = "int32_t";
            f->num_dim = 0;
            f->data = (void *) &p->waypoints_num;
            return 0;
        }
        
        case 1: {
            f->name = "waypoints";
            f->type = LCM_FIELD_DOUBLE;
            f->typestr = "double";
            f->num_dim = 2;
            f->dim_size[0] = p->waypoints_num;
            f->dim_size[1] = 2;
            f->dim_is_variable[0] = 1;
            f->dim_is_variable[1] = 0;
            f->data = (void *) &p->waypoints;
            return 0;
        }
        
        case 2: {
            f->name = "speed";
            f->type = LCM_FIELD_DOUBLE;
            f->typestr = "double";
            f->num_dim = 0;
            f->data = (void *) &p->speed;
            return 0;
        }
        
        default:
            return 1;
    }
}

const lcm_type_info_t *arm_path_t_get_type_info(void)
{
    static int init = 0;
    static lcm_type_info_t typeinfo;
    if (!init) {
        typeinfo.encode         = (lcm_encode_t) arm_path_t_encode;
        typeinfo.decode         = (lcm_decode_t) arm_path_t_decode;
        typeinfo.decode_cleanup = (lcm_decode_cleanup_t) arm_path_t_decode_cleanup;
        typeinfo.encoded_size   = (lcm_encoded_size_t) arm_path_t_encoded_size;
        typeinfo.struct_size    = (lcm_struct_size_t)  arm_path_t_struct_size;
        typeinfo.num_fields     = (lcm_num_fields_t) arm_path_t_num_fields;
        typeinfo.get_field      = (lcm_get_field_t) arm_path_t_get_field;
        typeinfo.get_hash       = (lcm_get_hash_t) __arm_path_t_get_hash;
    }
    
    return &typeinfo;
}
int __arm_path_t_decode_array(const void *buf, int offset, int maxlen, arm_path_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].waypoints_num), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        p[element].waypoints = (double**) lcm_malloc(sizeof(double*) * p[element].waypoints_num);
        { int a;
        for (a = 0; a < p[element].waypoints_num; a++) {
            p[element].waypoints[a] = (double*) lcm_malloc(sizeof(double) * 2);
            thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].waypoints[a], 2);
            if (thislen < 0) return thislen; else pos += thislen;
        }
        }

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, &(p[element].speed), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __arm_path_t_decode_array_cleanup(arm_path_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int32_t_decode_array_cleanup(&(p[element].waypoints_num), 1);

        { int a;
        for (a = 0; a < p[element].waypoints_num; a++) {
            __double_decode_array_cleanup(p[element].waypoints[a], 2);
            if (p[element].waypoints[a]) free(p[element].waypoints[a]);
        }
        }
        if (p[element].waypoints) free(p[element].waypoints);

        __double_decode_array_cleanup(&(p[element].speed), 1);

    }
    return 0;
}

int arm_path_t_decode(const void *buf, int offset, int maxlen, arm_path_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __arm_path_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __arm_path_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int arm_path_t_decode_cleanup(arm_path_t *p)
{
    return __arm_path_t_decode_array_cleanup(p, 1);
}

int __arm_path_t_clone_array(const arm_path_t *p, arm_path_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int32_t_clone_array(&(p[element].waypoints_num), &(q[element].waypoints_num), 1);

        q[element].waypoints = (double**) lcm_malloc(sizeof(double*) * q[element].waypoints_num);
        { int a;
        for (a = 0; a < p[element].waypoints_num; a++) {
            q[element].waypoints[a] = (double*) lcm_malloc(sizeof(double) * 2);
            __double_clone_array(p[element].waypoints[a], q[element].waypoints[a], 2);
        }
        }

        __double_clone_array(&(p[element].speed), &(q[element].speed), 1);

    }
    return 0;
}

arm_path_t *arm_path_t_copy(const arm_path_t *p)
{
    arm_path_t *q = (arm_path_t*) malloc(sizeof(arm_path_t));
    __arm_path_t_clone_array(p, q, 1);
    return q;
}

void arm_path_t_destroy(arm_path_t *p)
{
    __arm_path_t_decode_array_cleanup(p, 1);
    free(p);
}

int arm_path_t_publish(lcm_t *lc, const char *channel, const arm_path_t *p)
{
      int max_data_size = arm_path_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = arm_path_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _arm_path_t_subscription_t {
    arm_path_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void arm_path_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    arm_path_t p;
    memset(&p, 0, sizeof(arm_path_t));
    status = arm_path_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding arm_path_t!!!\n", status);
        return;
    }

    arm_path_t_subscription_t *h = (arm_path_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    arm_path_t_decode_cleanup (&p);
}

arm_path_t_subscription_t* arm_path_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    arm_path_t_handler_t f, void *userdata)
{
    arm_path_t_subscription_t *n = (arm_path_t_subscription_t*)
                       malloc(sizeof(arm_path_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 arm_path_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg arm_path_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int arm_path_t_subscription_set_queue_capacity (arm_path_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int arm_path_t_unsubscribe(lcm_t *lcm, arm_path_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe arm_path_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}
