/*************************************************************************************************
 * Ruby binding of Kyoto Cabinet
 *                                                               Copyright (C) 2009-2010 FAL Labs
 * This file is part of Kyoto Cabinet.
 * This program is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation, either version
 * 3 of the License, or any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************************************/


#include <kcpolydb.h>

namespace kc = kyotocabinet;

extern "C" {

#include <ruby.h>

#if RUBY_VM >= 1
#define _KC_YARV_
#endif


// precedent type declaration
class CursorBurrow;
struct SoftCursor;
class SoftVisitor;
class SoftBlockVisitor;
class SoftEachVisitor;
class SoftEachKeyVisitor;
class SoftEachValueVisitor;
class SoftFileProcessor;
class SoftBlockFileProcessor;
class NativeFunction;
typedef std::map<std::string, std::string> StringMap;
typedef std::vector<std::string> StringVector;
typedef VALUE (*METHOD)(...);


// function prototypes
void Init_kyotocabinet();
static VALUE StringValueEx(VALUE vobj);
static VALUE rb_str_new_ex(VALUE vdb, const char* ptr, size_t size);
static VALUE rb_str_new_ex2(VALUE vdb, const char* str);
static VALUE findclass(const char* name);
static VALUE findclass_impl(VALUE args);
static VALUE maptovhash(VALUE vdb, const StringMap* map);
static VALUE vectortovarray(VALUE vdb, const StringVector* vec);
static void define_module();
static VALUE kc_conv_str(VALUE vself, VALUE vstr);
static VALUE kc_atoi(VALUE vself, VALUE vstr);
static VALUE kc_atoix(VALUE vself, VALUE vstr);
static VALUE kc_atof(VALUE vself, VALUE vstr);
static VALUE kc_hash_murmur(VALUE vself, VALUE vstr);
static VALUE kc_hash_fnv(VALUE vself, VALUE vstr);
static void threadyield();
static void define_err();
static void err_define_child(const char* name, uint32_t code);
static VALUE err_initialize(int argc, VALUE* argv, VALUE vself);
static VALUE err_set(VALUE vself, VALUE vcode, VALUE vmessage);
static VALUE err_code(VALUE vself);
static VALUE err_name(VALUE vself);
static VALUE err_message(VALUE vself);
static VALUE err_to_s(VALUE vself);
static VALUE err_inspect(VALUE vself);
static VALUE err_op_eq(VALUE vself, VALUE vright);
static VALUE err_op_ne(VALUE vself, VALUE vright);
static void define_vis();
static VALUE vis_magic_initialize(VALUE vself, VALUE vnum);
static VALUE vis_visit_full(VALUE vself, VALUE vkey, VALUE vvalue);
static VALUE vis_visit_empty(VALUE vself, VALUE vkey);
static void define_fproc();
static VALUE fproc_process(VALUE vself, VALUE vpath);
static void define_cur();
static VALUE cur_new(VALUE cls);
static void cur_del(void* ptr);
static VALUE cur_initialize(VALUE vself, VALUE vdb);
static VALUE cur_disable(VALUE vself);
static VALUE cur_accept(int argc, VALUE* argv, VALUE vself);
static VALUE cur_set_value(int argc, VALUE* argv, VALUE vself);
static VALUE cur_remove(VALUE vself);
static VALUE cur_get_key(int argc, VALUE* argv, VALUE vself);
static VALUE cur_get_value(int argc, VALUE* argv, VALUE vself);
static VALUE cur_get(int argc, VALUE* argv, VALUE vself);
static VALUE cur_seize(VALUE vself);
static VALUE cur_jump(int argc, VALUE* argv, VALUE vself);
static VALUE cur_jump_back(int argc, VALUE* argv, VALUE vself);
static VALUE cur_step(VALUE vself);
static VALUE cur_step_back(VALUE vself);
static VALUE cur_db(VALUE vself);
static VALUE cur_error(VALUE vself);
static VALUE cur_to_s(VALUE vself);
static VALUE cur_inspect(VALUE vself);
static void define_db();
static VALUE db_new(VALUE cls);
static void db_del(void* ptr);
static void db_raise(VALUE vself);
static VALUE db_initialize(int argc, VALUE* argv, VALUE vself);
static VALUE db_error(VALUE vself);
static VALUE db_open(int argc, VALUE* argv, VALUE vself);
static VALUE db_close(VALUE vself);
static VALUE db_accept(int argc, VALUE* argv, VALUE vself);
static VALUE db_accept_bulk(int argc, VALUE* argv, VALUE vself);
static VALUE db_iterate(int argc, VALUE* argv, VALUE vself);
static VALUE db_set(VALUE vself, VALUE vkey, VALUE vvalue);
static VALUE db_add(VALUE vself, VALUE vkey, VALUE vvalue);
static VALUE db_replace(VALUE vself, VALUE vkey, VALUE vvalue);
static VALUE db_append(VALUE vself, VALUE vkey, VALUE vvalue);
static VALUE db_increment(int argc, VALUE* argv, VALUE vself);
static VALUE db_increment_double(int argc, VALUE* argv, VALUE vself);
static VALUE db_cas(VALUE vself, VALUE vkey, VALUE voval, VALUE vnval);
static VALUE db_remove(VALUE vself, VALUE vkey);
static VALUE db_get(VALUE vself, VALUE vkey);
static VALUE db_seize(VALUE vself, VALUE vkey);
static VALUE db_set_bulk(int argc, VALUE* argv, VALUE vself);
static VALUE db_remove_bulk(int argc, VALUE* argv, VALUE vself);
static VALUE db_get_bulk(int argc, VALUE* argv, VALUE vself);
static VALUE db_clear(VALUE vself);
static VALUE db_synchronize(int argc, VALUE* argv, VALUE vself);
static VALUE db_occupy(int argc, VALUE* argv, VALUE vself);
static VALUE db_copy(VALUE vself, VALUE vdest);
static VALUE db_begin_transaction(int argc, VALUE* argv, VALUE vself);
static VALUE db_end_transaction(int argc, VALUE* argv, VALUE vself);
static VALUE db_transaction(int argc, VALUE* argv, VALUE vself);
static VALUE db_transaction_body(VALUE args);
static VALUE db_transaction_ensure(VALUE args);
static VALUE db_dump_snapshot(VALUE vself, VALUE vdest);
static VALUE db_load_snapshot(VALUE vself, VALUE vsrc);
static VALUE db_count(VALUE vself);
static VALUE db_size(VALUE vself);
static VALUE db_path(VALUE vself);
static VALUE db_status(VALUE vself);
static VALUE db_match_prefix(int argc, VALUE* argv, VALUE vself);
static VALUE db_match_regex(int argc, VALUE* argv, VALUE vself);
static VALUE db_merge(int argc, VALUE* argv, VALUE vself);
static VALUE db_cursor(VALUE vself);
static VALUE db_cursor_process(VALUE vself);
static VALUE db_cursor_process_body(VALUE vargs);
static VALUE db_cursor_process_ensure(VALUE vargs);
static VALUE db_tune_exception_rule(VALUE vself, VALUE vcodes);
static VALUE db_tune_encoding(VALUE vself, VALUE vencname);
static VALUE db_tune_encoding_impl(VALUE args);
static VALUE db_to_s(VALUE vself);
static VALUE db_inspect(VALUE vself);
static VALUE db_shift(VALUE vself);
static char* db_shift_impl(kc::PolyDB* db, size_t* ksp, const char** vbp, size_t* vsp);
static VALUE db_each(VALUE vself);
static VALUE db_each_key(VALUE vself);
static VALUE db_each_value(VALUE vself);
static VALUE db_process(int argc, VALUE* argv, VALUE vself);
static VALUE db_process_body(VALUE args);
static VALUE db_process_ensure(VALUE args);


// global variables
const int32_t VISMAGICNOP = kc::INT32MAX / 4 + 0;
const int32_t VISMAGICREMOVE = kc::INT32MAX / 4 + 1;
VALUE mod_kc;
VALUE cls_ex;
VALUE cls_str;
VALUE cls_enc;
VALUE cls_th;
VALUE cls_mtx;
VALUE cls_err;
VALUE cls_err_children[(int)kc::PolyDB::Error::MISC+1];
VALUE cls_vis;
VALUE cls_vis_magic;
VALUE cls_fproc;
VALUE cls_cur;
VALUE cls_db;
ID id_str_force_encoding;
ID id_enc_find;
ID id_th_pass;
ID id_mtx_lock;
ID id_mtx_unlock;
ID id_obj_to_str;
ID id_obj_to_s;
ID id_hash_keys;
ID id_err_code;
ID id_err_message;
ID id_vis_magic;
ID id_vis_nop;
ID id_vis_remove;
ID id_vis_visit_full;
ID id_vis_visit_empty;
ID id_fproc_process;
ID id_cur_db;
ID id_cur_disable;
ID id_db_error;
ID id_db_open;
ID id_db_close;
ID id_db_begin_transaction;
ID id_db_end_transaction;
ID id_db_exbits;
ID id_db_mutex;
ID id_db_enc;


/**
 * Generic options.
 */
enum GenericOption {
  GEXCEPTIONAL = 1 << 0,
  GCONCURRENT = 1 << 1
};


/**
 * Burrow of cursors no longer in use.
 */
class CursorBurrow {
 private:
  typedef std::vector<kc::PolyDB::Cursor*> CursorList;
 public:
  explicit CursorBurrow() : dcurs_() {}
  ~CursorBurrow() {
    sweap();
  }
  void sweap() {
    if (dcurs_.size() > 0) {
      CursorList::iterator dit = dcurs_.begin();
      CursorList::iterator ditend = dcurs_.end();
      while (dit != ditend) {
        kc::PolyDB::Cursor* cur = *dit;
        delete cur;
        dit++;
      }
      dcurs_.clear();
    }
  }
  void deposit(kc::PolyDB::Cursor* cur) {
    dcurs_.push_back(cur);
  }
 private:
  CursorList dcurs_;
} g_curbur;


/**
 * Wrapper of a cursor.
 */
struct SoftCursor {
  kc::PolyDB::Cursor* cur_;
  SoftCursor() : cur_(NULL) {}
  ~SoftCursor() {
    if (cur_) g_curbur.deposit(cur_);
  }
};


/**
 * Wrapper of a visitor.
 */
class SoftVisitor : public kc::PolyDB::Visitor {
 public:
  explicit SoftVisitor(VALUE vdb, VALUE vvisitor, bool writable) :
      vdb_(vdb), vvisitor_(vvisitor), writable_(writable), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  const char* visit_full(const char* kbuf, size_t ksiz,
                         const char* vbuf, size_t vsiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vdb_, vbuf, vsiz);
    volatile VALUE args = rb_ary_new3(3, vvisitor_, vkey, vvalue);
    int result = 0;
    volatile VALUE vrv = rb_protect(visit_full_impl, args, &result);
    const char* rv;
    if (result) {
      emsg_ = "exception occurred during call back function";
      rv = NOP;
    } else if (rb_obj_is_kind_of(vrv, cls_vis_magic)) {
      volatile VALUE vmagic = rb_ivar_get(vrv, id_vis_magic);
      int32_t num = NUM2INT(vmagic);
      if (num == VISMAGICREMOVE) {
        if (writable_) {
          rv = kc::PolyDB::Visitor::REMOVE;
        } else {
          emsg_ = "confliction with the read-only parameter";
          rv = NOP;
        }
      } else {
        rv = kc::PolyDB::Visitor::NOP;
      }
    } else if (vrv == Qnil || vrv == Qfalse) {
      rv = NOP;
    } else if (!writable_) {
      emsg_ = "confliction with the read-only parameter";
      rv = NOP;
    } else {
      vrv = StringValueEx(vrv);
      rv = RSTRING_PTR(vrv);
      *sp = RSTRING_LEN(vrv);
    }
    return rv;
  }
  const char* visit_empty(const char* kbuf, size_t ksiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE args = rb_ary_new3(2, vvisitor_, vkey);
    int result = 0;
    volatile VALUE vrv = rb_protect(visit_empty_impl, args, &result);
    const char* rv;
    if (result) {
      emsg_ = "exception occurred during call back function";
      rv = NOP;
    } else if (rb_obj_is_kind_of(vrv, cls_vis_magic)) {
      volatile VALUE vmagic = rb_ivar_get(vrv, id_vis_magic);
      int32_t num = NUM2INT(vmagic);
      if (num == VISMAGICREMOVE) {
        if (writable_) {
          rv = kc::PolyDB::Visitor::REMOVE;
        } else {
          emsg_ = "confliction with the read-only parameter";
          rv = NOP;
        }
      } else {
        rv = kc::PolyDB::Visitor::NOP;
      }
    } else if (vrv == Qnil || vrv == Qfalse) {
      rv = NOP;
    } else if (!writable_) {
      emsg_ = "confliction with the read-only parameter";
      rv = NOP;
    } else {
      vrv = StringValueEx(vrv);
      rv = RSTRING_PTR(vrv);
      *sp = RSTRING_LEN(vrv);
    }
    return rv;
  }
  static VALUE visit_full_impl(VALUE args) {
    volatile VALUE vvisitor = rb_ary_shift(args);
    volatile VALUE vkey = rb_ary_shift(args);
    volatile VALUE vvalue = rb_ary_shift(args);
    return rb_funcall(vvisitor, id_vis_visit_full, 2, vkey, vvalue);
  }
  static VALUE visit_empty_impl(VALUE args) {
    volatile VALUE vvisitor = rb_ary_shift(args);
    volatile VALUE vkey = rb_ary_shift(args);
    return rb_funcall(vvisitor, id_vis_visit_empty, 1, vkey);
  }
  volatile VALUE vdb_;
  volatile VALUE vvisitor_;
  bool writable_;
  const char* emsg_;
};


/**
 * Wrapper of a visitor of the block paramter.
 */
class SoftBlockVisitor : public kc::PolyDB::Visitor {
 public:
  explicit SoftBlockVisitor(VALUE vdb, bool writable) :
      vdb_(vdb), writable_(writable), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  const char* visit_full(const char* kbuf, size_t ksiz,
                         const char* vbuf, size_t vsiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vdb_, vbuf, vsiz);
    volatile VALUE args = rb_ary_new3(2, vkey, vvalue);
    int result = 0;
    volatile VALUE vrv = rb_protect(visit_impl, args, &result);
    const char* rv;
    if (result) {
      emsg_ = "exception occurred during call back function";
      rv = NOP;
    } else if (rb_obj_is_kind_of(vrv, cls_vis_magic)) {
      volatile VALUE vmagic = rb_ivar_get(vrv, id_vis_magic);
      int32_t num = NUM2INT(vmagic);
      if (num == VISMAGICREMOVE) {
        if (writable_) {
          rv = kc::PolyDB::Visitor::REMOVE;
        } else {
          emsg_ = "confliction with the read-only parameter";
          rv = NOP;
        }
      } else {
        rv = kc::PolyDB::Visitor::NOP;
      }
    } else if (vrv == Qnil || vrv == Qfalse) {
      rv = NOP;
    } else if (!writable_) {
      emsg_ = "confliction with the read-only parameter";
      rv = NOP;
    } else {
      vrv = StringValueEx(vrv);
      rv = RSTRING_PTR(vrv);
      *sp = RSTRING_LEN(vrv);
    }
    return rv;
  }
  const char* visit_empty(const char* kbuf, size_t ksiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE args = rb_ary_new3(2, vkey, Qnil);
    int result = 0;
    volatile VALUE vrv = rb_protect(visit_impl, args, &result);
    const char* rv;
    if (result) {
      emsg_ = "exception occurred during call back function";
      rv = NOP;
    } else if (rb_obj_is_kind_of(vrv, cls_vis_magic)) {
      volatile VALUE vmagic = rb_ivar_get(vrv, id_vis_magic);
      int32_t num = NUM2INT(vmagic);
      if (num == VISMAGICREMOVE) {
        if (writable_) {
          rv = kc::PolyDB::Visitor::REMOVE;
        } else {
          emsg_ = "confliction with the read-only parameter";
          rv = NOP;
        }
      } else {
        rv = kc::PolyDB::Visitor::NOP;
      }
    } else if (vrv == Qnil || vrv == Qfalse) {
      rv = NOP;
    } else if (!writable_) {
      emsg_ = "confliction with the read-only parameter";
      rv = NOP;
    } else {
      vrv = StringValueEx(vrv);
      rv = RSTRING_PTR(vrv);
      *sp = RSTRING_LEN(vrv);
    }
    return rv;
  }
  static VALUE visit_impl(VALUE args) {
    return rb_yield(args);
  }
  volatile VALUE vdb_;
  bool writable_;
  const char* emsg_;
};


/**
 * Wrapper of a visitor for the each method.
 */
class SoftEachVisitor : public kc::PolyDB::Visitor {
 public:
  explicit SoftEachVisitor(VALUE vdb) : vdb_(vdb), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  const char* visit_full(const char* kbuf, size_t ksiz,
                         const char* vbuf, size_t vsiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vdb_, vbuf, vsiz);
    volatile VALUE args = rb_ary_new3(2, vkey, vvalue);
    int result = 0;
    rb_protect(visit_full_impl, args, &result);
    if (result) emsg_ = "exception occurred during call back function";
    return NOP;
  }
  static VALUE visit_full_impl(VALUE args) {
    return rb_yield(args);
  }
  volatile VALUE vdb_;
  const char* emsg_;
};


/**
 * Wrapper of a visitor for the each_key method.
 */
class SoftEachKeyVisitor : public kc::PolyDB::Visitor {
 public:
  explicit SoftEachKeyVisitor(VALUE vdb) : vdb_(vdb), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  const char* visit_full(const char* kbuf, size_t ksiz,
                         const char* vbuf, size_t vsiz, size_t* sp) {
    volatile VALUE vkey = rb_str_new_ex(vdb_, kbuf, ksiz);
    volatile VALUE args = rb_ary_new3(1, vkey);
    int result = 0;
    rb_protect(visit_full_impl, args, &result);
    if (result) emsg_ = "exception occurred during call back function";
    return NOP;
  }
  static VALUE visit_full_impl(VALUE args) {
    return rb_yield(args);
  }
  volatile VALUE vdb_;
  const char* emsg_;
};


/**
 * Wrapper of a visitor for the each_value method.
 */
class SoftEachValueVisitor : public kc::PolyDB::Visitor {
 public:
  explicit SoftEachValueVisitor(VALUE vdb) : vdb_(vdb), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  const char* visit_full(const char* kbuf, size_t ksiz,
                         const char* vbuf, size_t vsiz, size_t* sp) {
    volatile VALUE vvalue = rb_str_new_ex(vdb_, vbuf, vsiz);
    volatile VALUE args = rb_ary_new3(1, vvalue);
    int result = 0;
    rb_protect(visit_full_impl, args, &result);
    if (result) emsg_ = "exception occurred during call back function";
    return NOP;
  }
  static VALUE visit_full_impl(VALUE args) {
    return rb_yield(args);
  }
  volatile VALUE vdb_;
  const char* emsg_;
};


/**
 * Wrapper of a file processor.
 */
class SoftFileProcessor : public kc::PolyDB::FileProcessor {
 public:
  explicit SoftFileProcessor(VALUE vdb, VALUE vproc) : vdb_(vdb), vproc_(vproc), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  bool process(const std::string& path, int64_t count, int64_t size) {
    volatile VALUE vpath = rb_str_new_ex2(vdb_, path.c_str());
    volatile VALUE vcount = LL2NUM(count);
    volatile VALUE vsize = LL2NUM(size);
    volatile VALUE args = rb_ary_new3(4, vproc_, vpath, vcount, vsize);
    int result = 0;
    volatile VALUE vrv = rb_protect(process_impl, args, &result);
    if (result) emsg_ = "exception occurred during call back function";
    return !result && vrv != Qnil && vrv != Qfalse;
  }
  static VALUE process_impl(VALUE args) {
    volatile VALUE vproc = rb_ary_shift(args);
    volatile VALUE vpath = rb_ary_shift(args);
    volatile VALUE vcount = rb_ary_shift(args);
    volatile VALUE vsize = rb_ary_shift(args);
    return rb_funcall(vproc, id_fproc_process, 3, vpath, vcount, vsize);
  }
  volatile VALUE vdb_;
  volatile VALUE vproc_;
  const char* emsg_;
};


/**
 * Wrapper of a file processor of the block parameter.
 */
class SoftBlockFileProcessor : public kc::PolyDB::FileProcessor {
 public:
  explicit SoftBlockFileProcessor(VALUE vdb) : vdb_(vdb), emsg_(NULL) {}
  const char* emsg() {
    return emsg_;
  }
 private:
  bool process(const std::string& path, int64_t count, int64_t size) {
    volatile VALUE vpath = rb_str_new_ex2(vdb_, path.c_str());
    volatile VALUE vcount = LL2NUM(count);
    volatile VALUE vsize = LL2NUM(size);
    volatile VALUE args = rb_ary_new3(3, vpath, vcount, vsize);
    int result = 0;
    volatile VALUE vrv = rb_protect(process_impl, args, &result);
    if (result) emsg_ = "exception occurred during call back function";
    return !result && vrv != Qnil && vrv != Qfalse;
  }
  static VALUE process_impl(VALUE args) {
    return rb_yield(args);
  }
  volatile VALUE vdb_;
  const char* emsg_;
};


/**
 * Wrapper of a native function.
 */
class NativeFunction {
 public:
  virtual ~NativeFunction() {}
  virtual void operate() = 0;
  static void execute(NativeFunction* func) {
#if defined(_KC_YARV_)
    rb_thread_blocking_region(execute_impl, func, RUBY_UBF_IO, NULL);
#else
    func->operate();
#endif
  }
 private:
  static VALUE execute_impl(void* ptr) {
    NativeFunction* func = (NativeFunction*)ptr;
    func->operate();
    return Qnil;
  }
};


/**
 * Entry point of the library.
 */
void Init_kyotocabinet() {
  define_module();
  define_err();
  define_vis();
  define_fproc();
  define_cur();
  define_db();
}


/**
 * Generate a string expression of an arbitrary object.
 */
static VALUE StringValueEx(VALUE vobj) {
  switch (TYPE(vobj)) {
    case T_STRING: {
      return vobj;
    }
    case T_FIXNUM: {
      char kbuf[kc::NUMBUFSIZ];
      size_t ksiz = std::sprintf(kbuf, "%d", (int)FIX2INT(vobj));
      return rb_str_new(kbuf, ksiz);
    }
    case T_NIL: {
      return rb_str_new("", 0);
    }
  }
  if (rb_respond_to(vobj, id_obj_to_str)) return StringValue(vobj);
  if (rb_respond_to(vobj, id_obj_to_s)) return rb_funcall(vobj, id_obj_to_s, 0);
  char kbuf[kc::NUMBUFSIZ*2];
  std::sprintf(kbuf, "#<Object:0x%llx>", (long long)rb_obj_id(vobj));
  return rb_str_new2(kbuf);
}


/**
 * Generate a string object with the internal encoding of the database.
 */
static VALUE rb_str_new_ex(VALUE vdb, const char* ptr, size_t size) {
  volatile VALUE venc = rb_ivar_get(vdb, id_db_enc);
  if (venc == Qnil) return rb_str_new(ptr, size);
  volatile VALUE vstr = rb_str_new(ptr, size);
  rb_funcall(vstr, id_str_force_encoding, 1, venc);
  return vstr;
}


/**
 * Generate a string object with the internal encoding of the database.
 */
static VALUE rb_str_new_ex2(VALUE vdb, const char* str) {
  volatile VALUE venc = rb_ivar_get(vdb, id_db_enc);
  if (venc == Qnil) return rb_str_new2(str);
  volatile VALUE vstr = rb_str_new2(str);
  rb_funcall(vstr, id_str_force_encoding, 1, venc);
  return vstr;
}


/**
 * Find the class object of a name.
 */
static VALUE findclass(const char* name) {
  volatile VALUE vname = rb_str_new2(name);
  volatile VALUE args = rb_ary_new3(1, vname);
  int result = 0;
  volatile VALUE cls = rb_protect(findclass_impl, args, &result);
  if (result) return Qnil;
  return cls;
}


/**
 * Find the class object of a name.
 */
static VALUE findclass_impl(VALUE args) {
  volatile VALUE vname = rb_ary_shift(args);
  return rb_path2class(RSTRING_PTR(vname));
}


/**
 * Convert an internal map to a Ruby hash.
 */
static VALUE maptovhash(VALUE vdb, const StringMap* map) {
  volatile VALUE vhash = rb_hash_new();
  StringMap::const_iterator it = map->begin();
  StringMap::const_iterator itend = map->end();
  while (it != itend) {
    volatile VALUE vkey = rb_str_new_ex(vdb, it->first.data(), it->first.size());
    volatile VALUE vvalue = rb_str_new_ex(vdb, it->second.data(), it->second.size());
    rb_hash_aset(vhash, vkey, vvalue);
    it++;
  }
  return vhash;
}


/**
 * Convert an internal vector to a Ruby array.
 */
static VALUE vectortovarray(VALUE vdb, const StringVector* vec) {
  volatile VALUE vary = rb_ary_new2(vec->size());
  StringVector::const_iterator it = vec->begin();
  StringVector::const_iterator itend = vec->end();
  while (it != itend) {
    volatile VALUE vstr = rb_str_new_ex(vdb, it->data(), it->size());
    rb_ary_push(vary, vstr);
    it++;
  }
  return vary;
}


/**
 * Pass the current execution state.
 */
static void threadyield() {
  rb_funcall(cls_th, id_th_pass, 0);
}


/**
 * Define objects of the module.
 */
static void define_module() {
  mod_kc = rb_define_module("KyotoCabinet");
  rb_require("thread");
  rb_define_const(mod_kc, "VERSION", rb_str_new2(kc::VERSION));
  rb_define_method(mod_kc, "conv_str", (METHOD)kc_conv_str, 1);
  rb_define_method(mod_kc, "atoi", (METHOD)kc_atoi, 1);
  rb_define_method(mod_kc, "atoix", (METHOD)kc_atoix, 1);
  rb_define_method(mod_kc, "atof", (METHOD)kc_atof, 1);
  rb_define_method(mod_kc, "hash_murmur", (METHOD)kc_hash_murmur, 1);
  rb_define_method(mod_kc, "hash_fnv", (METHOD)kc_hash_fnv, 1);
  cls_ex = findclass("RuntimeError");
  cls_str = findclass("String");
  id_str_force_encoding = rb_intern("force_encoding");
  cls_enc = findclass("Encoding");
  id_enc_find = rb_intern("find");
  cls_th = findclass("Thread");
  id_th_pass = rb_intern("pass");
  cls_mtx = findclass("Mutex");
  id_mtx_lock = rb_intern("lock");
  id_mtx_unlock = rb_intern("unlock");
  id_obj_to_str = rb_intern("to_str");
  id_obj_to_s = rb_intern("to_s");
  id_hash_keys = rb_intern("keys");
}


/**
 * Implementation of conv_str.
 */
static VALUE kc_conv_str(VALUE vself, VALUE vstr) {
  return StringValueEx(vstr);
}


/**
 * Implementation of atoi.
 */
static VALUE kc_atoi(VALUE vself, VALUE vstr) {
  vstr = StringValueEx(vstr);
  int64_t num = kc::atoi(RSTRING_PTR(vstr));
  return LL2NUM(num);
}


/**
 * Implementation of atoix.
 */
static VALUE kc_atoix(VALUE vself, VALUE vstr) {
  vstr = StringValueEx(vstr);
  int64_t num = kc::atoix(RSTRING_PTR(vstr));
  return LL2NUM(num);
}


/**
 * Implementation of atof.
 */
static VALUE kc_atof(VALUE vself, VALUE vstr) {
  vstr = StringValueEx(vstr);
  double num = kc::atof(RSTRING_PTR(vstr));
  return rb_float_new(num);
}


/**
 * Implementation of hash_murmur.
 */
static VALUE kc_hash_murmur(VALUE vself, VALUE vstr) {
  vstr = StringValueEx(vstr);
  uint64_t hash = kc::hashmurmur(RSTRING_PTR(vstr), RSTRING_LEN(vstr));
  return ULL2NUM(hash);
}


/**
 * Implementation of fnv.
 */
static VALUE kc_hash_fnv(VALUE vself, VALUE vstr) {
  vstr = StringValueEx(vstr);
  uint64_t hash = kc::hashfnv(RSTRING_PTR(vstr), RSTRING_LEN(vstr));
  return ULL2NUM(hash);
}


/**
 * Define objects of the Error class.
 */
static void define_err() {
  cls_err = rb_define_class_under(mod_kc, "Error", cls_ex);
  for (size_t i = 0; i < sizeof(cls_err_children) / sizeof(*cls_err_children); i++) {
    cls_err_children[i] = Qnil;
  }
  err_define_child("SUCCESS", kc::PolyDB::Error::SUCCESS);
  err_define_child("NOIMPL", kc::PolyDB::Error::NOIMPL);
  err_define_child("INVALID", kc::PolyDB::Error::INVALID);
  err_define_child("NOREPOS", kc::PolyDB::Error::NOREPOS);
  err_define_child("NOPERM", kc::PolyDB::Error::NOPERM);
  err_define_child("BROKEN", kc::PolyDB::Error::BROKEN);
  err_define_child("DUPREC", kc::PolyDB::Error::DUPREC);
  err_define_child("NOREC", kc::PolyDB::Error::NOREC);
  err_define_child("LOGIC", kc::PolyDB::Error::LOGIC);
  err_define_child("SYSTEM", kc::PolyDB::Error::SYSTEM);
  err_define_child("MISC", kc::PolyDB::Error::MISC);
  rb_define_private_method(cls_err, "initialize", (METHOD)err_initialize, -1);
  rb_define_method(cls_err, "set", (METHOD)err_set, 2);
  rb_define_method(cls_err, "code", (METHOD)err_code, 0);
  rb_define_method(cls_err, "name", (METHOD)err_name, 0);
  rb_define_method(cls_err, "message", (METHOD)err_message, 0);
  rb_define_method(cls_err, "to_i", (METHOD)err_code, 0);
  rb_define_method(cls_err, "to_s", (METHOD)err_to_s, 0);
  rb_define_method(cls_err, "inspect", (METHOD)err_inspect, 0);
  rb_define_method(cls_err, "==", (METHOD)err_op_eq, 1);
  rb_define_method(cls_err, "!=", (METHOD)err_op_ne, 1);
  id_err_code = rb_intern("@code");
  id_err_message = rb_intern("@message");
}


/**
 * Define the constant and the subclass of an error code.
 */
static void err_define_child(const char* name, uint32_t code) {
  rb_define_const(cls_err, name, INT2FIX(code));
  char xname[kc::NUMBUFSIZ];
  sprintf(xname, "X%s", name);
  cls_err_children[code] = rb_define_class_under(cls_err, xname, cls_err);
}


/**
 * Implementation of initialize.
 */
static VALUE err_initialize(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vcode, vmessage;
  rb_scan_args(argc, argv, "02", &vcode, &vmessage);
  if (argc == 1 && TYPE(vcode) == T_STRING) {
    const char* expr = RSTRING_PTR(vcode);
    uint32_t code = kc::atoi(expr);
    const char* rp = std::strchr(expr, ':');
    if (rp) expr = rp + 1;
    while (*expr == ' ') {
      expr++;
    }
    vcode = INT2FIX(code);
    vmessage = rb_str_new2(expr);
  } else {
    if (vcode == Qnil) vcode = INT2FIX(kc::PolyDB::Error::SUCCESS);
    if (vmessage == Qnil) vmessage = rb_str_new2("error");
  }
  rb_ivar_set(vself, id_err_code, vcode);
  rb_ivar_set(vself, id_err_message, vmessage);
  return Qnil;
}


/**
 * Implementation of set.
 */
static VALUE err_set(VALUE vself, VALUE vcode, VALUE vmessage) {
  rb_ivar_set(vself, id_err_code, vcode);
  rb_ivar_set(vself, id_err_message, vmessage);
  return Qnil;
}


/**
 * Implementation of code.
 */
static VALUE err_code(VALUE vself) {
  return rb_ivar_get(vself, id_err_code);
}


/**
 * Implementation of name.
 */
static VALUE err_name(VALUE vself) {
  int32_t code = FIX2INT(rb_ivar_get(vself, id_err_code));
  return rb_str_new2(kc::PolyDB::Error::codename((kc::PolyDB::Error::Code)code));
}


/**
 * Implementation of message.
 */
static VALUE err_message(VALUE vself) {
  return rb_ivar_get(vself, id_err_message);
}


/**
 * Implementation of to_s.
 */
static VALUE err_to_s(VALUE vself) {
  int32_t code = NUM2INT(rb_ivar_get(vself, id_err_code));
  volatile VALUE vmessage = rb_ivar_get(vself, id_err_message);
  const char* message = RSTRING_PTR(vmessage);
  std::string str = kc::strprintf("%s: %s",
                                  kc::PolyDB::Error::codename((kc::PolyDB::Error::Code)code),
                                  message);
  return rb_str_new(str.data(), str.size());
}


/**
 * Implementation of inspect.
 */
static VALUE err_inspect(VALUE vself) {
  int32_t code = NUM2INT(rb_ivar_get(vself, id_err_code));
  volatile VALUE vmessage = rb_ivar_get(vself, id_err_message);
  const char* message = RSTRING_PTR(vmessage);
  std::string str = kc::strprintf("#<KyotoCabinet::Error: %d: %s: %s>", code,
                                  kc::PolyDB::Error::codename((kc::PolyDB::Error::Code)code),
                                  message);
  return rb_str_new(str.data(), str.size());
}


/**
 * Implementation of op_eq.
 */
static VALUE err_op_eq(VALUE vself, VALUE vright) {
  if (vright == Qnil) return Qfalse;
  if (TYPE(vright) == T_FIXNUM)
    return NUM2INT(rb_ivar_get(vself, id_err_code)) == FIX2INT(vright) ? Qtrue : Qfalse;
  return NUM2INT(rb_ivar_get(vself, id_err_code)) == NUM2INT(rb_ivar_get(vright, id_err_code)) ?
      Qtrue : Qfalse;
}


/**
 * Implementation of op_ne.
 */
static VALUE err_op_ne(VALUE vself, VALUE vright) {
  if (vright == Qnil) return Qtrue;
  if (TYPE(vright) == T_FIXNUM)
    return NUM2INT(rb_ivar_get(vself, id_err_code)) != FIX2INT(vright) ? Qtrue : Qfalse;
  return NUM2INT(rb_ivar_get(vself, id_err_code)) != NUM2INT(rb_ivar_get(vright, id_err_code)) ?
      Qtrue : Qfalse;
}


/**
 * Define objects of the Visitor class.
 */
static void define_vis() {
  cls_vis = rb_define_class_under(mod_kc, "Visitor", rb_cObject);
  cls_vis_magic = rb_define_class_under(mod_kc, "VisitorMagic", rb_cObject);
  rb_define_private_method(cls_vis_magic, "initialize", (METHOD)vis_magic_initialize, 1);
  id_vis_magic = rb_intern("@magic_");
  volatile VALUE vnopnum = INT2FIX(VISMAGICNOP);
  volatile VALUE vnop = rb_class_new_instance(1, (VALUE*)&vnopnum, cls_vis_magic);
  rb_define_const(cls_vis, "NOP", vnop);
  volatile VALUE vremovenum = INT2FIX(VISMAGICREMOVE);
  volatile VALUE vremove = rb_class_new_instance(1, (VALUE*)&vremovenum, cls_vis_magic);
  rb_define_const(cls_vis, "REMOVE", vremove);
  rb_define_method(cls_vis, "visit_full", (METHOD)vis_visit_full, 2);
  rb_define_method(cls_vis, "visit_empty", (METHOD)vis_visit_empty, 1);
  id_vis_nop = rb_intern("NOP");
  id_vis_remove = rb_intern("REMOVE");
  id_vis_visit_full = rb_intern("visit_full");
  id_vis_visit_empty = rb_intern("visit_empty");
}


/**
 * Implementation of magic_initialize.
 */
static VALUE vis_magic_initialize(VALUE vself, VALUE vnum) {
  rb_ivar_set(vself, id_vis_magic, vnum);
  return Qnil;
}


/**
 * Implementation of visit_full.
 */
static VALUE vis_visit_full(VALUE vself, VALUE vkey, VALUE vvalue) {
  return rb_const_get(cls_vis, id_vis_nop);
}


/**
 * Implementation of visit_empty.
 */
static VALUE vis_visit_empty(VALUE vself, VALUE vkey) {
  return rb_const_get(cls_vis, id_vis_nop);
}


/**
 * Define objects of the FileProcessor class.
 */
static void define_fproc() {
  cls_fproc = rb_define_class_under(mod_kc, "FileProcessor", rb_cObject);
  rb_define_method(cls_fproc, "process", (METHOD)fproc_process, 1);
  id_fproc_process = rb_intern("process");
}


/**
 * Implementation of process.
 */
static VALUE fproc_process(VALUE vself, VALUE vpath) {
  return Qtrue;
}


/**
 * Define objects of the Cursor class.
 */
static void define_cur() {
  cls_cur = rb_define_class_under(mod_kc, "Cursor", rb_cObject);
  rb_define_alloc_func(cls_cur, cur_new);
  rb_define_private_method(cls_cur, "initialize", (METHOD)cur_initialize, 1);
  rb_define_method(cls_cur, "disable", (METHOD)cur_disable, 0);
  rb_define_method(cls_cur, "accept", (METHOD)cur_accept, -1);
  rb_define_method(cls_cur, "set_value", (METHOD)cur_set_value, -1);
  rb_define_method(cls_cur, "remove", (METHOD)cur_remove, 0);
  rb_define_method(cls_cur, "get_key", (METHOD)cur_get_key, -1);
  rb_define_method(cls_cur, "get_value", (METHOD)cur_get_value, -1);
  rb_define_method(cls_cur, "get", (METHOD)cur_get, -1);
  rb_define_method(cls_cur, "seize", (METHOD)cur_seize, 0);
  rb_define_method(cls_cur, "jump", (METHOD)cur_jump, -1);
  rb_define_method(cls_cur, "jump_back", (METHOD)cur_jump_back, -1);
  rb_define_method(cls_cur, "step", (METHOD)cur_step, 0);
  rb_define_method(cls_cur, "step_back", (METHOD)cur_step_back, 0);
  rb_define_method(cls_cur, "db", (METHOD)cur_db, 0);
  rb_define_method(cls_cur, "error", (METHOD)cur_error, 0);
  rb_define_method(cls_cur, "to_s", (METHOD)cur_to_s, 0);
  rb_define_method(cls_cur, "inspect", (METHOD)cur_inspect, 0);
  id_cur_db = rb_intern("@db_");
  id_cur_disable= rb_intern("disable");
}


/**
 * Implementation of new.
 */
static VALUE cur_new(VALUE cls) {
  SoftCursor* cur = new SoftCursor;
  return Data_Wrap_Struct(cls_cur, 0, cur_del, cur);
}


/**
 * Implementation of del.
 */
static void cur_del(void* ptr) {
  delete (SoftCursor*)ptr;
}


/**
 * Implementation of initialize.
 */
static VALUE cur_initialize(VALUE vself, VALUE vdb) {
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  if (!rb_obj_is_kind_of(vdb, cls_db)) return Qnil;
  kc::PolyDB* db;
  Data_Get_Struct(vdb, kc::PolyDB, db);
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    g_curbur.sweap();
    cur->cur_ = db->cursor();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    g_curbur.sweap();
    cur->cur_ = db->cursor();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (cur->cur_) {
    rb_ivar_set(vself, id_cur_db, vdb);
  } else {
    rb_ivar_set(vself, id_cur_db, Qnil);
  }
  return Qnil;
}


/**
 * Implementation of disable.
 */
static VALUE cur_disable(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    delete cur->cur_;
    cur->cur_ = NULL;
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    delete cur->cur_;
    cur->cur_ = NULL;
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  rb_ivar_set(vself, id_cur_db, Qnil);
  return Qnil;
}


/**
 * Implementation of accept.
 */
static VALUE cur_accept(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vvisitor, vwritable, vstep;
  rb_scan_args(argc, argv, "03", &vvisitor, &vwritable, &vstep);
  volatile VALUE vrv;
  if (vvisitor == Qnil) {
    bool writable = vwritable != Qfalse;
    bool step = vstep != Qnil && vstep != Qfalse;
    SoftBlockVisitor visitor(vdb, writable);
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      cur->cur_->db()->set_error(kc::PolyDB::Error::INVALID, "unsuppotred method");
      db_raise(vdb);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = cur->cur_->accept(&visitor, writable, step);
    const char *emsg = visitor.emsg();
    if (emsg) {
      cur->cur_->db()->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  } else {
    bool writable = vwritable != Qfalse;
    bool step = vstep != Qnil && vstep != Qfalse;
    SoftVisitor visitor(vdb, vvisitor, writable);
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      cur->cur_->db()->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vdb);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = cur->cur_->accept(&visitor, writable, step);
    const char *emsg = visitor.emsg();
    if (emsg) {
      cur->cur_->db()->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  }
  return vrv;
}


/**
 * Implementation of set_value.
 */
static VALUE cur_set_value(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vvalue, vstep;
  rb_scan_args(argc, argv, "11", &vvalue, &vstep);
  vvalue = StringValueEx(vvalue);
  const char* vbuf = RSTRING_PTR(vvalue);
  size_t vsiz = RSTRING_LEN(vvalue);
  bool step = vstep != Qnil && vstep != Qfalse;
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur, const char* vbuf, size_t vsiz, bool step) :
          cur_(cur), vbuf_(vbuf), vsiz_(vsiz), step_(step), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = cur_->set_value(vbuf_, vsiz_, step_);
      }
      kc::PolyDB::Cursor* cur_;
      const char* vbuf_;
      size_t vsiz_;
      bool step_;
      bool rv_;
    } func(cur->cur_, vbuf, vsiz, step);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = cur->cur_->set_value(vbuf, vsiz, step);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vdb);
  return Qfalse;
}


/**
 * Implementation of remove.
 */
static VALUE cur_remove(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur) : cur_(cur), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = cur_->remove();
      }
      kc::PolyDB::Cursor* cur_;
      bool rv_;
    } func(cur->cur_);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = cur->cur_->remove();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vdb);
  return Qfalse;
}


/**
 * Implementation of get_key.
 */
static VALUE cur_get_key(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vstep;
  rb_scan_args(argc, argv, "01", &vstep);
  bool step = vstep != Qnil && vstep != Qfalse;
  char* kbuf;
  size_t ksiz;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur, bool step) :
          cur_(cur), step_(step), kbuf_(NULL), ksiz_(0) {}
      char* rv(size_t* ksp) {
        *ksp = ksiz_;
        return kbuf_;
      }
     private:
      void operate() {
        kbuf_ = cur_->get_key(&ksiz_, step_);
      }
      kc::PolyDB::Cursor* cur_;
      bool step_;
      char* kbuf_;
      size_t ksiz_;
    } func(cur->cur_, step);
    NativeFunction::execute(&func);
    kbuf = func.rv(&ksiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kbuf = cur->cur_->get_key(&ksiz, step);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (kbuf) {
    vrv = rb_str_new_ex(vdb, kbuf, ksiz);
    delete[] kbuf;
  } else {
    vrv = Qnil;
    db_raise(vdb);
  }
  return vrv;
}


/**
 * Implementation of get_value.
 */
static VALUE cur_get_value(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vstep;
  rb_scan_args(argc, argv, "01", &vstep);
  bool step = vstep != Qnil && vstep != Qfalse;
  char* vbuf;
  size_t vsiz;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur, bool step) :
          cur_(cur), step_(step), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* vsp) {
        *vsp = vsiz_;
        return vbuf_;
      }
     private:
      void operate() {
        vbuf_ = cur_->get_value(&vsiz_, step_);
      }
      kc::PolyDB::Cursor* cur_;
      bool step_;
      char* vbuf_;
      size_t vsiz_;
    } func(cur->cur_, step);
    NativeFunction::execute(&func);
    vbuf = func.rv(&vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    vbuf = cur->cur_->get_value(&vsiz, step);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (vbuf) {
    vrv = rb_str_new_ex(vdb, vbuf, vsiz);
    delete[] vbuf;
  } else {
    vrv = Qnil;
    db_raise(vdb);
  }
  return vrv;
}


/**
 * Implementation of get.
 */
static VALUE cur_get(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vstep;
  rb_scan_args(argc, argv, "01", &vstep);
  bool step = vstep != Qnil && vstep != Qfalse;
  char* kbuf;
  const char* vbuf;
  size_t ksiz, vsiz;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur, bool step) :
          cur_(cur), step_(step), kbuf_(NULL), ksiz_(0), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* ksp, const char** vbp, size_t* vsp) {
        *ksp = ksiz_;
        *vbp = vbuf_;
        *vsp = vsiz_;
        return kbuf_;
      }
     private:
      void operate() {
        kbuf_ = cur_->get(&ksiz_, &vbuf_, &vsiz_, step_);
      }
      kc::PolyDB::Cursor* cur_;
      bool step_;
      char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
    } func(cur->cur_, step);
    NativeFunction::execute(&func);
    kbuf = func.rv(&ksiz, &vbuf, &vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kbuf = cur->cur_->get(&ksiz, &vbuf, &vsiz, step);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (kbuf) {
    volatile VALUE vkey = rb_str_new_ex(vdb, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vdb, vbuf, vsiz);
    vrv = rb_ary_new3(2, vkey, vvalue);
    delete[] kbuf;
  } else {
    vrv = Qnil;
    db_raise(vdb);
  }
  return vrv;
}


/**
 * Implementation of seize.
 */
static VALUE cur_seize(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  char* kbuf;
  const char* vbuf;
  size_t ksiz, vsiz;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur) :
          cur_(cur), kbuf_(NULL), ksiz_(0), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* ksp, const char** vbp, size_t* vsp) {
        *ksp = ksiz_;
        *vbp = vbuf_;
        *vsp = vsiz_;
        return kbuf_;
      }
     private:
      void operate() {
        kbuf_ = cur_->seize(&ksiz_, &vbuf_, &vsiz_);
      }
      kc::PolyDB::Cursor* cur_;
      char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
    } func(cur->cur_);
    NativeFunction::execute(&func);
    kbuf = func.rv(&ksiz, &vbuf, &vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kbuf = cur->cur_->seize(&ksiz, &vbuf, &vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (kbuf) {
    volatile VALUE vkey = rb_str_new_ex(vdb, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vdb, vbuf, vsiz);
    vrv = rb_ary_new3(2, vkey, vvalue);
    delete[] kbuf;
  } else {
    vrv = Qnil;
    db_raise(vdb);
  }
  return vrv;
}


/**
 * Implementation of jump.
 */
static VALUE cur_jump(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vkey;
  rb_scan_args(argc, argv, "01", &vkey);
  volatile VALUE vrv;
  if (vkey == Qnil) {
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB::Cursor* cur) : cur_(cur), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = cur_->jump();
        }
        kc::PolyDB::Cursor* cur_;
        bool rv_;
      } func(cur->cur_);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = cur->cur_->jump();
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  } else {
    vkey = StringValueEx(vkey);
    const char* kbuf = RSTRING_PTR(vkey);
    size_t ksiz = RSTRING_LEN(vkey);
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB::Cursor* cur, const char*kbuf, size_t ksiz) :
            cur_(cur), kbuf_(kbuf), ksiz_(ksiz), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = cur_->jump(kbuf_, ksiz_);
        }
        kc::PolyDB::Cursor* cur_;
        const char* kbuf_;
        size_t ksiz_;
        bool rv_;
      } func(cur->cur_, kbuf, ksiz);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = cur->cur_->jump(kbuf, ksiz);
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  }
  return vrv;
}


/**
 * Implementation of jump_back.
 */
static VALUE cur_jump_back(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  volatile VALUE vkey;
  rb_scan_args(argc, argv, "01", &vkey);
  volatile VALUE vrv;
  if (vkey == Qnil) {
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB::Cursor* cur) : cur_(cur), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = cur_->jump_back();
        }
        kc::PolyDB::Cursor* cur_;
        bool rv_;
      } func(cur->cur_);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = cur->cur_->jump_back();
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  } else {
    vkey = StringValueEx(vkey);
    const char* kbuf = RSTRING_PTR(vkey);
    size_t ksiz = RSTRING_LEN(vkey);
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB::Cursor* cur, const char*kbuf, size_t ksiz) :
            cur_(cur), kbuf_(kbuf), ksiz_(ksiz), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = cur_->jump_back(kbuf_, ksiz_);
        }
        kc::PolyDB::Cursor* cur_;
        const char* kbuf_;
        size_t ksiz_;
        bool rv_;
      } func(cur->cur_, kbuf, ksiz);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = cur->cur_->jump_back(kbuf, ksiz);
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vdb);
    }
  }
  return vrv;
}


/**
 * Implementation of step.
 */
static VALUE cur_step(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur) : cur_(cur), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = cur_->step();
      }
      kc::PolyDB::Cursor* cur_;
      bool rv_;
    } func(cur->cur_);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = cur->cur_->step();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vdb);
  return Qfalse;
}


/**
 * Implementation of step_back.
 */
static VALUE cur_step_back(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qfalse;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB::Cursor* cur) : cur_(cur), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = cur_->step_back();
      }
      kc::PolyDB::Cursor* cur_;
      bool rv_;
    } func(cur->cur_);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = cur->cur_->step_back();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vdb);
  return Qfalse;
}


/**
 * Implementation of db.
 */
static VALUE cur_db(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  return vdb;
}


/**
 * Implementation of error.
 */
static VALUE cur_error(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return Qnil;
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  kc::PolyDB::Error err = cur->cur_->error();
  volatile VALUE args[2];
  args[0] = INT2FIX(err.code());
  args[1] = rb_str_new_ex2(vdb, err.message());
  return rb_class_new_instance(2, (VALUE*)args, cls_err);
}


/**
 * Implementation of to_s.
 */
static VALUE cur_to_s(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return rb_str_new2("(disabled)");
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  std::string str;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    kc::PolyDB* db = cur->cur_->db();
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "%s: ", path.c_str());
    size_t ksiz;
    char* kbuf = cur->cur_->get_key(&ksiz);
    if (kbuf) {
      str.append(kbuf, ksiz);
      delete[] kbuf;
    } else {
      str.append("(nil)");
    }
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kc::PolyDB* db = cur->cur_->db();
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "%s: ", path.c_str());
    size_t ksiz;
    char* kbuf = cur->cur_->get_key(&ksiz);
    if (kbuf) {
      str.append(kbuf, ksiz);
      delete[] kbuf;
    } else {
      str.append("(nil)");
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  return rb_str_new_ex2(vdb, str.c_str());
}


/**
 * Implementation of inspect.
 */
static VALUE cur_inspect(VALUE vself) {
  volatile VALUE vdb = rb_ivar_get(vself, id_cur_db);
  if (vdb == Qnil) return rb_str_new2("#<KyotoCabinet::Cursor:(disabled)>");
  SoftCursor* cur;
  Data_Get_Struct(vself, SoftCursor, cur);
  std::string str;
  volatile VALUE vmutex = rb_ivar_get(vdb, id_db_mutex);
  if (vmutex == Qnil) {
    kc::PolyDB* db = cur->cur_->db();
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "#<KyotoCabinet::Cursor:%p: %s: ", cur, path.c_str());
    size_t ksiz;
    char* kbuf = cur->cur_->get_key(&ksiz);
    if (kbuf) {
      str.append(kbuf, ksiz);
      delete[] kbuf;
    } else {
      str.append("(nil)");
    }
    kc::strprintf(&str, ">");
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kc::PolyDB* db = cur->cur_->db();
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "#<KyotoCabinet::Cursor:%p: %s: ", cur, path.c_str());
    size_t ksiz;
    char* kbuf = cur->cur_->get_key(&ksiz);
    if (kbuf) {
      str.append(kbuf, ksiz);
      delete[] kbuf;
    } else {
      str.append("(nil)");
    }
    kc::strprintf(&str, ">");
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  return rb_str_new_ex2(vdb, str.c_str());
}


/**
 * Define objects of the DB class.
 */
static void define_db() {
  cls_db = rb_define_class_under(mod_kc, "DB", rb_cObject);
  rb_define_alloc_func(cls_db, db_new);
  rb_define_const(cls_db, "GEXCEPTIONAL", INT2FIX(GEXCEPTIONAL));
  rb_define_const(cls_db, "GCONCURRENT", INT2FIX(GCONCURRENT));
  rb_define_const(cls_db, "OREADER", INT2FIX(kc::PolyDB::OREADER));
  rb_define_const(cls_db, "OWRITER", INT2FIX(kc::PolyDB::OWRITER));
  rb_define_const(cls_db, "OCREATE", INT2FIX(kc::PolyDB::OCREATE));
  rb_define_const(cls_db, "OTRUNCATE", INT2FIX(kc::PolyDB::OTRUNCATE));
  rb_define_const(cls_db, "OAUTOTRAN", INT2FIX(kc::PolyDB::OAUTOTRAN));
  rb_define_const(cls_db, "OAUTOSYNC", INT2FIX(kc::PolyDB::OAUTOSYNC));
  rb_define_const(cls_db, "ONOLOCK", INT2FIX(kc::PolyDB::ONOLOCK));
  rb_define_const(cls_db, "OTRYLOCK", INT2FIX(kc::PolyDB::OTRYLOCK));
  rb_define_const(cls_db, "ONOREPAIR", INT2FIX(kc::PolyDB::ONOREPAIR));
  rb_define_const(cls_db, "MSET", INT2FIX(kc::PolyDB::MSET));
  rb_define_const(cls_db, "MADD", INT2FIX(kc::PolyDB::MADD));
  rb_define_const(cls_db, "MREPLACE", INT2FIX(kc::PolyDB::MREPLACE));
  rb_define_const(cls_db, "MAPPEND", INT2FIX(kc::PolyDB::MAPPEND));
  rb_define_private_method(cls_db, "initialize", (METHOD)db_initialize, -1);
  rb_define_method(cls_db, "error", (METHOD)db_error, 0);
  rb_define_method(cls_db, "open", (METHOD)db_open, -1);
  rb_define_method(cls_db, "close", (METHOD)db_close, 0);
  rb_define_method(cls_db, "accept", (METHOD)db_accept, -1);
  rb_define_method(cls_db, "accept_bulk", (METHOD)db_accept_bulk, -1);
  rb_define_method(cls_db, "iterate", (METHOD)db_iterate, -1);
  rb_define_method(cls_db, "set", (METHOD)db_set, 2);
  rb_define_method(cls_db, "add", (METHOD)db_add, 2);
  rb_define_method(cls_db, "replace", (METHOD)db_replace, 2);
  rb_define_method(cls_db, "append", (METHOD)db_append, 2);
  rb_define_method(cls_db, "increment", (METHOD)db_increment, -1);
  rb_define_method(cls_db, "increment_double", (METHOD)db_increment_double, -1);
  rb_define_method(cls_db, "cas", (METHOD)db_cas, 3);
  rb_define_method(cls_db, "remove", (METHOD)db_remove, 1);
  rb_define_method(cls_db, "get", (METHOD)db_get, 1);
  rb_define_method(cls_db, "seize", (METHOD)db_seize, 1);
  rb_define_method(cls_db, "set_bulk", (METHOD)db_set_bulk, -1);
  rb_define_method(cls_db, "remove_bulk", (METHOD)db_remove_bulk, -1);
  rb_define_method(cls_db, "get_bulk", (METHOD)db_get_bulk, -1);
  rb_define_method(cls_db, "clear", (METHOD)db_clear, 0);
  rb_define_method(cls_db, "synchronize", (METHOD)db_synchronize, -1);
  rb_define_method(cls_db, "occupy", (METHOD)db_occupy, -1);
  rb_define_method(cls_db, "copy", (METHOD)db_copy, 1);
  rb_define_method(cls_db, "begin_transaction", (METHOD)db_begin_transaction, -1);
  rb_define_method(cls_db, "end_transaction", (METHOD)db_end_transaction, -1);
  rb_define_method(cls_db, "transaction", (METHOD)db_transaction, -1);
  rb_define_method(cls_db, "dump_snapshot", (METHOD)db_dump_snapshot, 1);
  rb_define_method(cls_db, "load_snapshot", (METHOD)db_load_snapshot, 1);
  rb_define_method(cls_db, "count", (METHOD)db_count, 0);
  rb_define_method(cls_db, "size", (METHOD)db_size, 0);
  rb_define_method(cls_db, "path", (METHOD)db_path, 0);
  rb_define_method(cls_db, "status", (METHOD)db_status, 0);
  rb_define_method(cls_db, "match_prefix", (METHOD)db_match_prefix, -1);
  rb_define_method(cls_db, "match_regex", (METHOD)db_match_regex, -1);
  rb_define_method(cls_db, "merge", (METHOD)db_merge, -1);
  rb_define_method(cls_db, "cursor", (METHOD)db_cursor, 0);
  rb_define_method(cls_db, "cursor_process", (METHOD)db_cursor_process, 0);
  rb_define_method(cls_db, "tune_exception_rule", (METHOD)db_tune_exception_rule, 1);
  rb_define_method(cls_db, "tune_encoding", (METHOD)db_tune_encoding, 1);
  rb_define_method(cls_db, "to_s", (METHOD)db_to_s, 0);
  rb_define_method(cls_db, "inspect", (METHOD)db_inspect, 0);
  rb_define_method(cls_db, "[]", (METHOD)db_get, 1);
  rb_define_method(cls_db, "[]=", (METHOD)db_set, 2);
  rb_define_method(cls_db, "store", (METHOD)db_set, 2);
  rb_define_method(cls_db, "delete", (METHOD)db_remove, 1);
  rb_define_method(cls_db, "fetch", (METHOD)db_set, 1);
  rb_define_method(cls_db, "shift", (METHOD)db_shift, 0);
  rb_define_method(cls_db, "length", (METHOD)db_count, 0);
  rb_define_method(cls_db, "each", (METHOD)db_each, 0);
  rb_define_method(cls_db, "each_pair", (METHOD)db_each, 0);
  rb_define_method(cls_db, "each_key", (METHOD)db_each_key, 0);
  rb_define_method(cls_db, "each_value", (METHOD)db_each_value, 0);
  id_db_error = rb_intern("error");
  id_db_open = rb_intern("open");
  id_db_close = rb_intern("close");
  id_db_begin_transaction = rb_intern("begin_transaction");
  id_db_end_transaction = rb_intern("end_transaction");
  id_db_exbits = rb_intern("@exbits_");
  id_db_mutex = rb_intern("@mutex_");
  id_db_enc = rb_intern("@enc_");
  rb_define_singleton_method(cls_db, "process", (METHOD)db_process, -1);
}


/**
 * Implementation of new.
 */
static VALUE db_new(VALUE cls) {
  kc::PolyDB* db = new kc::PolyDB();
  return Data_Wrap_Struct(cls_db, 0, db_del, db);
}


/**
 * Implementation of del.
 */
static void db_del(void* ptr) {
  delete (kc::PolyDB*)ptr;
}


/**
 * Raise the exception of an error code.
 */
static void db_raise(VALUE vself) {
  volatile VALUE vexbits = rb_ivar_get(vself, id_db_exbits);
  if (vexbits == Qnil) return;
  uint32_t exbits = NUM2INT(vexbits);
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  kc::PolyDB::Error err = db->error();
  uint32_t code = err.code();
  if (exbits & (1 << code)) rb_raise(cls_err_children[code], "%u: %s", code, err.message());
}


/**
 * Implementation of initialize.
 */
static VALUE db_initialize(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vopts;
  rb_scan_args(argc, argv, "01", &vopts);
  int32_t opts = TYPE(vopts) == T_FIXNUM ? FIX2INT(vopts) : 0;
  volatile VALUE vexbits = Qnil;
  if (opts & GEXCEPTIONAL) {
    uint32_t exbits = 0;
    exbits |= 1 << kc::PolyDB::Error::NOIMPL;
    exbits |= 1 << kc::PolyDB::Error::INVALID;
    exbits |= 1 << kc::PolyDB::Error::NOREPOS;
    exbits |= 1 << kc::PolyDB::Error::NOPERM;
    exbits |= 1 << kc::PolyDB::Error::BROKEN;
    exbits |= 1 << kc::PolyDB::Error::SYSTEM;
    exbits |= 1 << kc::PolyDB::Error::MISC;
    vexbits = INT2FIX(exbits);
  }
  rb_ivar_set(vself, id_db_exbits, vexbits);
  volatile VALUE vmutex = (opts & GCONCURRENT) ? Qnil : rb_class_new_instance(0, NULL, cls_mtx);
  rb_ivar_set(vself, id_db_mutex, vmutex);
  rb_ivar_set(vself, id_db_enc, Qnil);
  rb_ivar_set(vself, id_db_enc, Qnil);
  return Qnil;
}


/**
 * Implementation of error.
 */
static VALUE db_error(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  kc::PolyDB::Error err = db->error();
  uint32_t code = err.code();
  volatile VALUE args[2];
  args[0] = INT2FIX(code);
  args[1] = rb_str_new_ex2(vself, err.message());
  return rb_class_new_instance(2, (VALUE*)args, cls_err_children[code]);
}


/**
 * Implementation of open.
 */
static VALUE db_open(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vpath, vmode;
  rb_scan_args(argc, argv, "02", &vpath, &vmode);
  if (vpath == Qnil) vpath = rb_str_new2(":");
  vpath = StringValueEx(vpath);
  const char* path = RSTRING_PTR(vpath);
  uint32_t mode = vmode == Qnil ? kc::PolyDB::OWRITER | kc::PolyDB::OCREATE : NUM2INT(vmode);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* path, uint32_t mode) :
          db_(db), path_(path), mode_(mode), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->open(path_, mode_);
      }
      kc::PolyDB* db_;
      const char* path_;
      uint32_t mode_;
      bool rv_;
    } func(db, path, mode);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->open(path, mode);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of close.
 */
static VALUE db_close(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db) : db_(db), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        g_curbur.sweap();
        rv_ = db_->close();
      }
      kc::PolyDB* db_;
      bool rv_;
    } func(db);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    g_curbur.sweap();
    rv = db->close();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of accept.
 */
static VALUE db_accept(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkey, vvisitor, vwritable;
  rb_scan_args(argc, argv, "12", &vkey, &vvisitor, &vwritable);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  volatile VALUE vrv;
  if (vvisitor == Qnil) {
    bool writable = vwritable != Qfalse;
    SoftBlockVisitor visitor(vself, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->accept(kbuf, ksiz, &visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else {
    bool writable = vwritable != Qfalse;
    SoftVisitor visitor(vself, vvisitor, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->accept(kbuf, ksiz, &visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  }
  return vrv;
}


/**
 * Implementation of accept_bulk.
 */
static VALUE db_accept_bulk(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkeys, vvisitor, vwritable;
  rb_scan_args(argc, argv, "12", &vkeys, &vvisitor, &vwritable);
  StringVector keys;
  if (TYPE(vkeys) == T_ARRAY) {
    int32_t knum = RARRAY_LEN(vkeys);
    for (int32_t i = 0; i < knum; i++) {
      volatile VALUE vkey = rb_ary_entry(vkeys, i);
      vkey = StringValueEx(vkey);
      keys.push_back(std::string(RSTRING_PTR(vkey), RSTRING_LEN(vkey)));
    }
  }
  volatile VALUE vrv;
  if (vvisitor == Qnil) {
    bool writable = vwritable != Qfalse;
    SoftBlockVisitor visitor(vself, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->accept_bulk(keys, &visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else {
    bool writable = vwritable != Qfalse;
    SoftVisitor visitor(vself, vvisitor, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->accept_bulk(keys, &visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  }
  return vrv;
}


/**
 * Implementation of iterate.
 */
static VALUE db_iterate(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vvisitor, vwritable;
  rb_scan_args(argc, argv, "02", &vvisitor, &vwritable);
  volatile VALUE vrv;
  if (vvisitor == Qnil) {
    bool writable = vwritable != Qfalse;
    SoftBlockVisitor visitor(vself, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->iterate(&visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else {
    bool writable = vwritable != Qfalse;
    SoftVisitor visitor(vself, vvisitor, writable);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->iterate(&visitor, writable);
    const char *emsg = visitor.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  }
  return vrv;
}


/**
 * Implementation of set.
 */
static VALUE db_set(VALUE vself, VALUE vkey, VALUE vvalue) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  vvalue = StringValueEx(vvalue);
  const char* vbuf = RSTRING_PTR(vvalue);
  size_t vsiz = RSTRING_LEN(vvalue);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        const char* vbuf, size_t vsiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(vbuf), vsiz_(vsiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->set(kbuf_, ksiz_, vbuf_, vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
      bool rv_;
    } func(db, kbuf, ksiz, vbuf, vsiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->set(kbuf, ksiz, vbuf, vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of add.
 */
static VALUE db_add(VALUE vself, VALUE vkey, VALUE vvalue) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  vvalue = StringValueEx(vvalue);
  const char* vbuf = RSTRING_PTR(vvalue);
  size_t vsiz = RSTRING_LEN(vvalue);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        const char* vbuf, size_t vsiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(vbuf), vsiz_(vsiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->add(kbuf_, ksiz_, vbuf_, vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
      bool rv_;
    } func(db, kbuf, ksiz, vbuf, vsiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->add(kbuf, ksiz, vbuf, vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of replace.
 */
static VALUE db_replace(VALUE vself, VALUE vkey, VALUE vvalue) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  vvalue = StringValueEx(vvalue);
  const char* vbuf = RSTRING_PTR(vvalue);
  size_t vsiz = RSTRING_LEN(vvalue);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        const char* vbuf, size_t vsiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(vbuf), vsiz_(vsiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->replace(kbuf_, ksiz_, vbuf_, vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
      bool rv_;
    } func(db, kbuf, ksiz, vbuf, vsiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->replace(kbuf, ksiz, vbuf, vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of append.
 */
static VALUE db_append(VALUE vself, VALUE vkey, VALUE vvalue) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  vvalue = StringValueEx(vvalue);
  const char* vbuf = RSTRING_PTR(vvalue);
  size_t vsiz = RSTRING_LEN(vvalue);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        const char* vbuf, size_t vsiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(vbuf), vsiz_(vsiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->append(kbuf_, ksiz_, vbuf_, vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
      bool rv_;
    } func(db, kbuf, ksiz, vbuf, vsiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->append(kbuf, ksiz, vbuf, vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of increment.
 */
static VALUE db_increment(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkey, vnum, vorig;
  rb_scan_args(argc, argv, "12", &vkey, &vnum, &vorig);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  int64_t num = 0;
  switch (TYPE(vnum)) {
    case T_FIXNUM: {
      num = FIX2INT(vnum);
      break;
    }
    case T_BIGNUM: {
      num = NUM2LL(vnum);
      break;
    }
    case T_FLOAT: {
      num = NUM2DBL(vnum);
      break;
    }
    case T_TRUE: {
      num = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vnum);
      num = kc::atoi(str);
      break;
    }
  }
  int64_t orig = 0;
  switch (TYPE(vorig)) {
    case T_FIXNUM: {
      orig = FIX2INT(vorig);
      break;
    }
    case T_BIGNUM: {
      orig = NUM2LL(vorig);
      break;
    }
    case T_FLOAT: {
      double dnum = NUM2DBL(vorig);
      if (kc::chknan(dnum)) {
        orig = kc::INT64MIN;
      } else if (kc::chkinf(dnum)) {
        orig = dnum < 0 ? kc::INT64MIN : kc::INT64MAX;
      } else {
        orig = dnum;
      }
      break;
    }
    case T_TRUE: {
      orig = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vorig);
      double dnum = kc::atof(str);
      if (kc::chknan(dnum)) {
        orig = kc::INT64MIN;
      } else if (kc::chkinf(dnum)) {
        orig = dnum < 0 ? kc::INT64MIN : kc::INT64MAX;
      } else {
        orig = dnum;
      }
      break;
    }
  }
  volatile VALUE vrv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        int64_t num, int64_t orig) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), num_(num), orig_(orig) {}
      int64_t rv() {
        return num_;
      }
     private:
      void operate() {
        num_ = db_->increment(kbuf_, ksiz_, num_, orig_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      int64_t num_;
      int64_t orig_;
    } func(db, kbuf, ksiz, num, orig);
    NativeFunction::execute(&func);
    num = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    num = db->increment(kbuf, ksiz, num, orig);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (num == kc::INT64MIN) {
    vrv = Qnil;
    db_raise(vself);
  } else {
    vrv = LL2NUM(num);
  }
  return vrv;
}


/**
 * Implementation of increment_double.
 */
static VALUE db_increment_double(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkey, vnum, vorig;
  rb_scan_args(argc, argv, "12", &vkey, &vnum, &vorig);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  double num = 0;
  switch (TYPE(vnum)) {
    case T_FIXNUM: {
      num = FIX2INT(vnum);
      break;
    }
    case T_BIGNUM: {
      num = NUM2LL(vnum);
      break;
    }
    case T_FLOAT: {
      num = NUM2DBL(vnum);
      break;
    }
    case T_TRUE: {
      num = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vnum);
      num = kc::atof(str);
      break;
    }
  }
  double orig = 0;
  switch (TYPE(vorig)) {
    case T_FIXNUM: {
      orig = FIX2INT(vorig);
      break;
    }
    case T_BIGNUM: {
      orig = NUM2LL(vorig);
      break;
    }
    case T_FLOAT: {
      orig = NUM2DBL(vorig);
      break;
    }
    case T_TRUE: {
      orig = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vorig);
      orig = kc::atof(str);
      break;
    }
  }
  volatile VALUE vrv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        double num, double orig) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), num_(num), orig_(orig) {}
      double rv() {
        return num_;
      }
     private:
      void operate() {
        num_ = db_->increment_double(kbuf_, ksiz_, num_, orig_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      double num_;
      double orig_;
    } func(db, kbuf, ksiz, num, orig);
    NativeFunction::execute(&func);
    num = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    num = db->increment_double(kbuf, ksiz, num, orig);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (kc::chknan(num)) {
    vrv = Qnil;
    db_raise(vself);
  } else {
    vrv = rb_float_new(num);
  }
  return vrv;
}



/**
 * Implementation of cas.
 */
static VALUE db_cas(VALUE vself, VALUE vkey, VALUE voval, VALUE vnval) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  const char* ovbuf = NULL;
  size_t ovsiz = 0;
  if (voval != Qnil) {
    voval = StringValueEx(voval);
    ovbuf = RSTRING_PTR(voval);
    ovsiz = RSTRING_LEN(voval);
  }
  const char* nvbuf = NULL;
  size_t nvsiz = 0;
  if (vnval != Qnil) {
    vnval = StringValueEx(vnval);
    nvbuf = RSTRING_PTR(vnval);
    nvsiz = RSTRING_LEN(vnval);
  }
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz,
                        const char* ovbuf, size_t ovsiz, const char* nvbuf, size_t nvsiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz),
          ovbuf_(ovbuf), ovsiz_(ovsiz), nvbuf_(nvbuf), nvsiz_(nvsiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->cas(kbuf_, ksiz_, ovbuf_, ovsiz_, nvbuf_, nvsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      const char* ovbuf_;
      size_t ovsiz_;
      const char* nvbuf_;
      size_t nvsiz_;
      bool rv_;
    } func(db, kbuf, ksiz, ovbuf, ovsiz, nvbuf, nvsiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->cas(kbuf, ksiz, ovbuf, ovsiz, nvbuf, nvsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of remove.
 */
static VALUE db_remove(VALUE vself, VALUE vkey) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->remove(kbuf_, ksiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      bool rv_;
    } func(db, kbuf, ksiz);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->remove(kbuf, ksiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of get.
 */
static VALUE db_get(VALUE vself, VALUE vkey) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  char* vbuf;
  size_t vsiz;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* vsp) {
        *vsp = vsiz_;
        return vbuf_;
      }
     private:
      void operate() {
        vbuf_ = db_->get(kbuf_, ksiz_, &vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      char* vbuf_;
      size_t vsiz_;
    } func(db, kbuf, ksiz);
    NativeFunction::execute(&func);
    vbuf = func.rv(&vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    vbuf = db->get(kbuf, ksiz, &vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (vbuf) {
    vrv = rb_str_new_ex(vself, vbuf, vsiz);
    delete[] vbuf;
  } else {
    vrv = Qnil;
    db_raise(vself);
  }
  return vrv;
}


/**
 * Implementation of seize.
 */
static VALUE db_seize(VALUE vself, VALUE vkey) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vkey = StringValueEx(vkey);
  const char* kbuf = RSTRING_PTR(vkey);
  size_t ksiz = RSTRING_LEN(vkey);
  char* vbuf;
  size_t vsiz;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* kbuf, size_t ksiz) :
          db_(db), kbuf_(kbuf), ksiz_(ksiz), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* vsp) {
        *vsp = vsiz_;
        return vbuf_;
      }
     private:
      void operate() {
        vbuf_ = db_->seize(kbuf_, ksiz_, &vsiz_);
      }
      kc::PolyDB* db_;
      const char* kbuf_;
      size_t ksiz_;
      char* vbuf_;
      size_t vsiz_;
    } func(db, kbuf, ksiz);
    NativeFunction::execute(&func);
    vbuf = func.rv(&vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    vbuf = db->seize(kbuf, ksiz, &vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (vbuf) {
    vrv = rb_str_new_ex(vself, vbuf, vsiz);
    delete[] vbuf;
  } else {
    vrv = Qnil;
    db_raise(vself);
  }
  return vrv;
}


/**
 * Implementation of set_bulk.
 */
static VALUE db_set_bulk(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vrecs, vatomic;
  rb_scan_args(argc, argv, "11", &vrecs, &vatomic);
  StringMap recs;
  if (TYPE(vrecs) == T_HASH) {
    VALUE vkeys = rb_funcall(vrecs, id_hash_keys, 0);
    int32_t knum = RARRAY_LEN(vkeys);
    for (int32_t i = 0; i < knum; i++) {
      volatile VALUE vkey = rb_ary_entry(vkeys, i);
      volatile VALUE vvalue = rb_hash_aref(vrecs, vkey);
      vkey = StringValueEx(vkey);
      vvalue = StringValueEx(vvalue);
      recs[std::string(RSTRING_PTR(vkey), RSTRING_LEN(vkey))] =
          std::string(RSTRING_PTR(vvalue), RSTRING_LEN(vvalue));
    }
  }
  bool atomic = vatomic != Qfalse;
  int64_t rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const StringMap* recs, bool atomic) :
          db_(db), recs_(recs), atomic_(atomic), rv_(0) {}
      int64_t rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->set_bulk(*recs_, atomic_);
      }
      kc::PolyDB* db_;
      const StringMap* recs_;
      bool atomic_;
      int64_t rv_;
    } func(db, &recs, atomic);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->set_bulk(recs, atomic);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv < 0) {
    db_raise(vself);
    return LL2NUM(-1);
  }
  return LL2NUM(rv);
}


/**
 * Implementation of remove_bulk.
 */
static VALUE db_remove_bulk(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkeys, vatomic;
  rb_scan_args(argc, argv, "11", &vkeys, &vatomic);
  StringVector keys;
  if (TYPE(vkeys) == T_ARRAY) {
    int32_t knum = RARRAY_LEN(vkeys);
    for (int32_t i = 0; i < knum; i++) {
      volatile VALUE vkey = rb_ary_entry(vkeys, i);
      vkey = StringValueEx(vkey);
      keys.push_back(std::string(RSTRING_PTR(vkey), RSTRING_LEN(vkey)));
    }
  }
  bool atomic = vatomic != Qfalse;
  int64_t rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const StringVector* keys, bool atomic) :
          db_(db), keys_(keys), atomic_(atomic), rv_(0) {}
      int64_t rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->remove_bulk(*keys_, atomic_);
      }
      kc::PolyDB* db_;
      const StringVector* keys_;
      bool atomic_;
      int64_t rv_;
    } func(db, &keys, atomic);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->remove_bulk(keys, atomic);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv < 0) {
    db_raise(vself);
    return LL2NUM(-1);
  }
  return LL2NUM(rv);
}


/**
 * Implementation of get_bulk.
 */
static VALUE db_get_bulk(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vkeys, vatomic;
  rb_scan_args(argc, argv, "11", &vkeys, &vatomic);
  StringVector keys;
  if (TYPE(vkeys) == T_ARRAY) {
    int32_t knum = RARRAY_LEN(vkeys);
    for (int32_t i = 0; i < knum; i++) {
      volatile VALUE vkey = rb_ary_entry(vkeys, i);
      vkey = StringValueEx(vkey);
      keys.push_back(std::string(RSTRING_PTR(vkey), RSTRING_LEN(vkey)));
    }
  }
  bool atomic = vatomic != Qfalse;
  StringMap recs;
  int64_t rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const StringVector* keys, StringMap* recs, bool atomic) :
          db_(db), keys_(keys), recs_(recs), atomic_(atomic), rv_(0) {}
      int64_t rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->get_bulk(*keys_, recs_, atomic_);
      }
      kc::PolyDB* db_;
      const StringVector* keys_;
      StringMap* recs_;
      bool atomic_;
      int64_t rv_;
    } func(db, &keys, &recs, atomic);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->get_bulk(keys, &recs, atomic);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv < 0) {
    db_raise(vself);
    return Qnil;
  }
  return maptovhash(vself, &recs);
}


/**
 * Implementation of clear.
 */
static VALUE db_clear(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db) : db_(db), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->clear();
      }
      kc::PolyDB* db_;
      bool rv_;
    } func(db);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->clear();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of synchronize.
 */
static VALUE db_synchronize(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vhard, vproc;
  rb_scan_args(argc, argv, "02", &vhard, &vproc);
  bool hard = vhard != Qnil && vhard != Qfalse;
  volatile VALUE vrv;
  if (rb_respond_to(vproc, id_fproc_process)) {
    SoftFileProcessor proc(vself, vproc);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->synchronize(hard, &proc);
    const char *emsg = proc.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else if (rb_block_given_p()) {
    SoftBlockFileProcessor proc(vself);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->synchronize(hard, &proc);
    const char *emsg = proc.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else {
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB* db, bool hard) : db_(db), hard_(hard), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = db_->synchronize(hard_, NULL);
        }
        kc::PolyDB* db_;
        bool hard_;
        bool rv_;
      } func(db, hard);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = db->synchronize(hard, NULL);
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  }
  return vrv;
}


/**
 * Implementation of occupy.
 */
static VALUE db_occupy(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vwritable, vproc;
  rb_scan_args(argc, argv, "02", &vwritable, &vproc);
  bool writable = vwritable != Qnil && vwritable != Qfalse;
  volatile VALUE vrv;
  if (rb_respond_to(vproc, id_fproc_process)) {
    SoftFileProcessor proc(vself, vproc);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->occupy(writable, &proc);
    const char *emsg = proc.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else if (rb_block_given_p()) {
    SoftBlockFileProcessor proc(vself);
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
      db_raise(vself);
      return Qnil;
    }
    rb_funcall(vmutex, id_mtx_lock, 0);
    bool rv = db->occupy(writable, &proc);
    const char *emsg = proc.emsg();
    if (emsg) {
      db->set_error(kc::PolyDB::Error::LOGIC, emsg);
      rv = false;
    }
    rb_funcall(vmutex, id_mtx_unlock, 0);
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  } else {
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      class FuncImpl : public NativeFunction {
       public:
        explicit FuncImpl(kc::PolyDB* db, bool writable) :
            db_(db), writable_(writable), rv_(false) {}
        bool rv() {
          return rv_;
        }
       private:
        void operate() {
          rv_ = db_->occupy(writable_, NULL);
        }
        kc::PolyDB* db_;
        bool writable_;
        bool rv_;
      } func(db, writable);
      NativeFunction::execute(&func);
      rv = func.rv();
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = db->occupy(writable, NULL);
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) {
      vrv = Qtrue;
    } else {
      vrv = Qfalse;
      db_raise(vself);
    }
  }
  return vrv;
}


/**
 * Implementation of copy.
 */
static VALUE db_copy(VALUE vself, VALUE vdest) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vdest = StringValueEx(vdest);
  const char* dest = RSTRING_PTR(vdest);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* dest) : db_(db), dest_(dest), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->copy(dest_);
      }
      kc::PolyDB* db_;
      const char* dest_;
      bool rv_;
    } func(db, dest);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->copy(dest);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of begin_transaction.
 */
static VALUE db_begin_transaction(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vhard;
  rb_scan_args(argc, argv, "01", &vhard);
  bool hard = vhard != Qnil && vhard != Qfalse;
  bool err = false;
  while (true) {
    bool rv;
    volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
    if (vmutex == Qnil) {
      rv = db->begin_transaction_try(hard);
    } else {
      rb_funcall(vmutex, id_mtx_lock, 0);
      rv = db->begin_transaction_try(hard);
      rb_funcall(vmutex, id_mtx_unlock, 0);
    }
    if (rv) break;
    if (db->error() != kc::PolyDB::Error::LOGIC) {
      err = true;
      break;
    }
    threadyield();
  }
  if (err) {
    db_raise(vself);
    return Qfalse;
  }
  return Qtrue;
}


/**
 * Implementation of end_transaction.
 */
static VALUE db_end_transaction(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vcommit;
  rb_scan_args(argc, argv, "01", &vcommit);
  bool commit = vcommit != Qfalse;
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    rv = db->end_transaction(commit);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->end_transaction(commit);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of transaction.
 */
static VALUE db_transaction(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vhard;
  rb_scan_args(argc, argv, "01", &vhard);
  volatile VALUE vrv = rb_funcall(vself, id_db_begin_transaction, 1, vhard);
  if (vrv == Qnil || vrv == Qfalse) return Qfalse;
  volatile VALUE vbargs = rb_ary_new3(1, vself);
  volatile VALUE veargs = rb_ary_new3(2, vself, vbargs);
  rb_ensure((METHOD)db_transaction_body, vbargs, (METHOD)db_transaction_ensure, veargs);
  return rb_ary_pop(veargs);
}


/**
 * Implementation of transaction_body.
 */
static VALUE db_transaction_body(VALUE vargs) {
  volatile VALUE vdb = rb_ary_shift(vargs);
  rb_ary_push(vargs, rb_yield(vdb));
  return Qnil;
}


/**
 * Implementation of transaction_ensure.
 */
static VALUE db_transaction_ensure(VALUE vargs) {
  volatile VALUE vdb = rb_ary_shift(vargs);
  volatile VALUE vbargs = rb_ary_shift(vargs);
  volatile VALUE vrv = rb_ary_shift(vbargs);
  volatile VALUE vcommit = vrv != Qnil && vrv != Qfalse ? Qtrue : Qfalse;
  vrv = rb_funcall(vdb, id_db_end_transaction, 1, vcommit);
  rb_ary_push(vargs, vrv);
  return Qnil;
}


/**
 * Implementation of dump_snapshot.
 */
static VALUE db_dump_snapshot(VALUE vself, VALUE vdest) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vdest = StringValueEx(vdest);
  const char* dest = RSTRING_PTR(vdest);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* dest) : db_(db), dest_(dest), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->dump_snapshot(dest_);
      }
      kc::PolyDB* db_;
      const char* dest_;
      bool rv_;
    } func(db, dest);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->dump_snapshot(dest);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of load_snapshot.
 */
static VALUE db_load_snapshot(VALUE vself, VALUE vsrc) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  vsrc = StringValueEx(vsrc);
  const char* src = RSTRING_PTR(vsrc);
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* src) : db_(db), src_(src), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->load_snapshot(src_);
      }
      kc::PolyDB* db_;
      const char* src_;
      bool rv_;
    } func(db, src);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->load_snapshot(src);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of count.
 */
static VALUE db_count(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  int64_t count;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    count = db->count();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    count = db->count();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (count < 0) db_raise(vself);
  return LL2NUM(count);
}


/**
 * Implementation of size.
 */
static VALUE db_size(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  int64_t size;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    size = db->size();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    size = db->size();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (size < 0) db_raise(vself);
  return LL2NUM(size);
}


/**
 * Implementation of path.
 */
static VALUE db_path(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  std::string path;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    path = db->path();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    path = db->path();
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (path.size() < 1) {
    db_raise(vself);
    return Qnil;
  }
  return rb_str_new_ex2(vself, path.c_str());
}


/**
 * Implementation of status.
 */
static VALUE db_status(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  StringMap status;
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    rv = db->status(&status);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->status(&status);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv) return maptovhash(vself, &status);
  db_raise(vself);
  return Qnil;
}


/**
 * Implementation of match_prefix.
 */
static VALUE db_match_prefix(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vprefix, vmax;
  rb_scan_args(argc, argv, "11", &vprefix, &vmax);
  vprefix = StringValueEx(vprefix);
  const char* pbuf = RSTRING_PTR(vprefix);
  size_t psiz = RSTRING_LEN(vprefix);
  int64_t max = -1;
  switch (TYPE(vmax)) {
    case T_FIXNUM: {
      max = FIX2INT(vmax);
      break;
    }
    case T_BIGNUM: {
      max = NUM2LL(vmax);
      break;
    }
    case T_FLOAT: {
      max = NUM2DBL(vmax);
      break;
    }
    case T_TRUE: {
      max = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vmax);
      max = kc::atoi(str);
      break;
    }
  }
  volatile VALUE vrv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  StringVector keys;
  int64_t rv;
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* pbuf, size_t psiz,
                        StringVector* keys, int64_t max) :
          db_(db), pbuf_(pbuf), psiz_(psiz), keys_(keys), max_(max), rv_(0) {}
      int64_t rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->match_prefix(std::string(pbuf_, psiz_), keys_, max_);
      }
      kc::PolyDB* db_;
      const char* pbuf_;
      size_t psiz_;
      StringVector* keys_;
      int64_t max_;
      int64_t rv_;
    } func(db, pbuf, psiz, &keys, max);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->match_prefix(std::string(pbuf, psiz), &keys, max);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv >= 0) {
    vrv = vectortovarray(vself, &keys);
  } else {
    vrv = Qnil;
    db_raise(vself);
  }
  return vrv;
}


/**
 * Implementation of match_regex.
 */
static VALUE db_match_regex(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vregex, vmax;
  rb_scan_args(argc, argv, "11", &vregex, &vmax);
  vregex = StringValueEx(vregex);
  const char* rbuf = RSTRING_PTR(vregex);
  size_t rsiz = RSTRING_LEN(vregex);
  int64_t max = -1;
  switch (TYPE(vmax)) {
    case T_FIXNUM: {
      max = FIX2INT(vmax);
      break;
    }
    case T_BIGNUM: {
      max = NUM2LL(vmax);
      break;
    }
    case T_FLOAT: {
      max = NUM2DBL(vmax);
      break;
    }
    case T_TRUE: {
      max = 1;
      break;
    }
    case T_STRING: {
      const char* str = RSTRING_PTR(vmax);
      max = kc::atoi(str);
      break;
    }
  }
  volatile VALUE vrv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  StringVector keys;
  int64_t rv;
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, const char* rbuf, size_t rsiz,
                        StringVector* keys, int64_t max) :
          db_(db), rbuf_(rbuf), rsiz_(rsiz), keys_(keys), max_(max), rv_(0) {}
      int64_t rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->match_regex(std::string(rbuf_, rsiz_), keys_, max_);
      }
      kc::PolyDB* db_;
      const char* rbuf_;
      size_t rsiz_;
      StringVector* keys_;
      int64_t max_;
      int64_t rv_;
    } func(db, rbuf, rsiz, &keys, max);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->match_regex(std::string(rbuf, rsiz), &keys, max);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  if (rv >= 0) {
    vrv = vectortovarray(vself, &keys);
  } else {
    vrv = Qnil;
    db_raise(vself);
  }
  return vrv;
}


/**
 * Implementation of merge.
 */
static VALUE db_merge(int argc, VALUE* argv, VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  volatile VALUE vsrcary, vmode;
  rb_scan_args(argc, argv, "11", &vsrcary, &vmode);
  if (TYPE(vsrcary) != T_ARRAY) return Qfalse;
  uint32_t mode = vmode == Qnil ? kc::PolyDB::MSET : NUM2INT(vmode);
  int32_t num = RARRAY_LEN(vsrcary);
  if (num < 1) return Qtrue;
  kc::BasicDB** srcary = new kc::BasicDB*[num];
  size_t srcnum = 0;
  for (int32_t i = 0; i < num; i++) {
    volatile VALUE vsrcdb = rb_ary_entry(vsrcary, i);
    if (rb_obj_is_kind_of(vsrcdb, cls_db)) {
      kc::PolyDB* srcdb;
      Data_Get_Struct(vsrcdb, kc::PolyDB, srcdb);
      srcary[srcnum++] = srcdb;
    }
  }
  bool rv;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db, kc::BasicDB** srcary, size_t srcnum, uint32_t mode) :
          db_(db), srcary_(srcary), srcnum_(srcnum), mode_(mode), rv_(false) {}
      bool rv() {
        return rv_;
      }
     private:
      void operate() {
        rv_ = db_->merge(srcary_, srcnum_, (kc::PolyDB::MergeMode)mode_);
      }
      kc::PolyDB* db_;
      kc::BasicDB** srcary_;
      size_t srcnum_;
      uint32_t mode_;
      bool rv_;
    } func(db, srcary, srcnum, mode);
    NativeFunction::execute(&func);
    rv = func.rv();
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    rv = db->merge(srcary, srcnum, (kc::PolyDB::MergeMode)mode);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  delete[] srcary;
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of cursor.
 */
static VALUE db_cursor(VALUE vself) {
  return rb_class_new_instance(1, &vself, cls_cur);
}


/**
 * Implementation of cursor_process.
 */
static VALUE db_cursor_process(VALUE vself) {
  volatile VALUE vcur = rb_class_new_instance(1, &vself, cls_cur);
  volatile VALUE vbargs = rb_ary_new3(1, vcur);
  volatile VALUE veargs = rb_ary_new3(1, vcur);
  rb_ensure((METHOD)db_cursor_process_body, vbargs, (METHOD)db_cursor_process_ensure, veargs);
  return Qnil;
}


/**
 * Implementation of cursor_process_body.
 */
static VALUE db_cursor_process_body(VALUE vargs) {
  volatile VALUE vcur = rb_ary_shift(vargs);
  rb_yield(vcur);
  return Qnil;
}


/**
 * Implementation of cursor_process_ensure.
 */
static VALUE db_cursor_process_ensure(VALUE vargs) {
  volatile VALUE vcur = rb_ary_shift(vargs);
  rb_funcall(vcur, id_cur_disable, 0);
  return Qnil;
}


/**
 * Implementation of tune_exception_rule.
 */
static VALUE db_tune_exception_rule(VALUE vself, VALUE vcodes) {
  if (TYPE(vcodes) != T_ARRAY) return Qfalse;
  uint32_t exbits = 0;
  int32_t num = RARRAY_LEN(vcodes);
  for (int32_t i = 0; i < num; i++) {
    volatile VALUE vcode = rb_ary_entry(vcodes, i);
    uint32_t code = NUM2INT(vcode);
    if (code <= kc::PolyDB::Error::MISC) exbits |= 1 << code;
  }
  volatile VALUE vexbits = exbits > 0 ? INT2FIX(exbits) : Qnil;
  rb_ivar_set(vself, id_db_exbits, vexbits);
  return Qtrue;
}


/**
 * Implementation of tune_encoding.
 */
static VALUE db_tune_encoding(VALUE vself, VALUE venc) {
  if (cls_enc == Qnil) return Qfalse;
  if (venc == Qnil) {
    rb_ivar_set(vself, id_db_enc, Qnil);
  } else if (rb_obj_is_instance_of(venc, cls_enc)) {
    rb_ivar_set(vself, id_db_enc, venc);
  } else {
    venc = StringValueEx(venc);
    volatile VALUE args = rb_ary_new3(1, venc);
    int result = 0;
    venc = rb_protect(db_tune_encoding_impl, args, &result);
    if (result) return Qfalse;
    rb_ivar_set(vself, id_db_enc, venc);
  }
  return Qtrue;
}


/**
 * Implementation of tune_encoding_impl.
 */
static VALUE db_tune_encoding_impl(VALUE args) {
  volatile VALUE venc = rb_ary_shift(args);
  return rb_funcall(cls_enc, id_enc_find, 1, venc);
}


/**
 * Implementation of to_s.
 */
static VALUE db_to_s(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  std::string str;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "%s: %lld: %lld",
                  path.c_str(), (long long)db->count(), (long long)db->size());
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "%s: %lld: %lld",
                  path.c_str(), (long long)db->count(), (long long)db->size());
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  return rb_str_new_ex2(vself, str.c_str());
}


/**
 * Implementation of inspect.
 */
static VALUE db_inspect(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  std::string str;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "#<KyotoCabinet::DB:%p: %s: %lld: %lld>",
                  db, path.c_str(), (long long)db->count(), (long long)db->size());
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    std::string path = db->path();
    if (path.size() < 1) path = "(nil)";
    kc::strprintf(&str, "#<KyotoCabinet::DB:%p: %s: %lld: %lld>",
                  db, path.c_str(), (long long)db->count(), (long long)db->size());
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  return rb_str_new_ex2(vself, str.c_str());
}


/**
 * Implementation of shift.
 */
static VALUE db_shift(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  char* kbuf;
  const char* vbuf;
  size_t ksiz, vsiz;
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    class FuncImpl : public NativeFunction {
     public:
      explicit FuncImpl(kc::PolyDB* db) :
          db_(db), kbuf_(NULL), ksiz_(0), vbuf_(NULL), vsiz_(0) {}
      char* rv(size_t* ksp, const char** vbp, size_t* vsp) {
        *ksp = ksiz_;
        *vbp = vbuf_;
        *vsp = vsiz_;
        return kbuf_;
      }
     private:
      void operate() {
        kbuf_ = db_shift_impl(db_, &ksiz_, &vbuf_, &vsiz_);
      }
      kc::PolyDB* db_;
      char* kbuf_;
      size_t ksiz_;
      const char* vbuf_;
      size_t vsiz_;
    } func(db);
    NativeFunction::execute(&func);
    kbuf = func.rv(&ksiz, &vbuf, &vsiz);
  } else {
    rb_funcall(vmutex, id_mtx_lock, 0);
    kbuf = db_shift_impl(db, &ksiz, &vbuf, &vsiz);
    rb_funcall(vmutex, id_mtx_unlock, 0);
  }
  volatile VALUE vrv;
  if (kbuf) {
    volatile VALUE vkey = rb_str_new_ex(vself, kbuf, ksiz);
    volatile VALUE vvalue = rb_str_new_ex(vself, vbuf, vsiz);
    vrv = rb_ary_new3(2, vkey, vvalue);
    delete[] kbuf;
  } else {
    vrv = Qnil;
    db_raise(vself);
  }
  return vrv;
}


static char* db_shift_impl(kc::PolyDB* db, size_t* ksp, const char** vbp, size_t* vsp) {
  kc::PolyDB::Cursor cur(db);
  if (!cur.jump()) return NULL;
  class VisitorImpl : public kc::PolyDB::Visitor {
   public:
    explicit VisitorImpl() : kbuf_(NULL), ksiz_(0), vbuf_(NULL), vsiz_(0) {}
    char* rv(size_t* ksp, const char** vbp, size_t* vsp) {
      *ksp = ksiz_;
      *vbp = vbuf_;
      *vsp = vsiz_;
      return kbuf_;
    }
   private:
    const char* visit_full(const char* kbuf, size_t ksiz,
                           const char* vbuf, size_t vsiz, size_t* sp) {
      size_t rsiz = ksiz + 1 + vsiz + 1;
      kbuf_ = new char[rsiz];
      std::memcpy(kbuf_, kbuf, ksiz);
      kbuf_[ksiz] = '\0';
      ksiz_ = ksiz;
      vbuf_ = kbuf_ + ksiz + 1;
      std::memcpy(vbuf_, vbuf, vsiz);
      vbuf_[vsiz] = '\0';
      vsiz_ = vsiz;
      return REMOVE;
    }
    char* kbuf_;
    size_t ksiz_;
    char* vbuf_;
    size_t vsiz_;
  } visitor;
  if (!cur.accept(&visitor, true, false)) return NULL;
  return visitor.rv(ksp, vbp, vsp);
}


/**
 * Implementation of each.
 */
static VALUE db_each(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  SoftEachVisitor visitor(vself);
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
    db_raise(vself);
    return Qnil;
  }
  rb_funcall(vmutex, id_mtx_lock, 0);
  bool rv = db->iterate(&visitor, false);
  const char *emsg = visitor.emsg();
  if (emsg) {
    db->set_error(kc::PolyDB::Error::LOGIC, emsg);
    rv = false;
  }
  rb_funcall(vmutex, id_mtx_unlock, 0);
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of each_key.
 */
static VALUE db_each_key(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  SoftEachKeyVisitor visitor(vself);
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
    db_raise(vself);
    return Qnil;
  }
  rb_funcall(vmutex, id_mtx_lock, 0);
  bool rv = db->iterate(&visitor, false);
  const char *emsg = visitor.emsg();
  if (emsg) {
    db->set_error(kc::PolyDB::Error::LOGIC, emsg);
    rv = false;
  }
  rb_funcall(vmutex, id_mtx_unlock, 0);
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of each_value.
 */
static VALUE db_each_value(VALUE vself) {
  kc::PolyDB* db;
  Data_Get_Struct(vself, kc::PolyDB, db);
  SoftEachValueVisitor visitor(vself);
  volatile VALUE vmutex = rb_ivar_get(vself, id_db_mutex);
  if (vmutex == Qnil) {
    db->set_error(kc::PolyDB::Error::INVALID, "unsupported method");
    db_raise(vself);
    return Qnil;
  }
  rb_funcall(vmutex, id_mtx_lock, 0);
  bool rv = db->iterate(&visitor, false);
  const char *emsg = visitor.emsg();
  if (emsg) {
    db->set_error(kc::PolyDB::Error::LOGIC, emsg);
    rv = false;
  }
  rb_funcall(vmutex, id_mtx_unlock, 0);
  if (rv) return Qtrue;
  db_raise(vself);
  return Qfalse;
}


/**
 * Implementation of process.
 */
static VALUE db_process(int argc, VALUE* argv, VALUE vself) {
  volatile VALUE vpath, vmode, vopts;
  rb_scan_args(argc, argv, "03", &vpath, &vmode, &vopts);
  volatile VALUE vdb = rb_class_new_instance(1, (VALUE*)&vopts, cls_db);
  volatile VALUE vrv = rb_funcall(vdb, id_db_open, 2, vpath, vmode);
  if (vrv == Qnil || vrv == Qfalse) return rb_funcall(vdb, id_db_error, 0);
  volatile VALUE vbargs = rb_ary_new3(1, vdb);
  volatile VALUE veargs = rb_ary_new3(1, vdb);
  rb_ensure((METHOD)db_process_body, vbargs, (METHOD)db_process_ensure, veargs);
  return rb_ary_pop(veargs);
}


/**
 * Implementation of process_body.
 */
static VALUE db_process_body(VALUE vargs) {
  volatile VALUE vdb = rb_ary_shift(vargs);
  rb_yield(vdb);
  return Qnil;
}


/**
 * Implementation of process_ensure.
 */
static VALUE db_process_ensure(VALUE vargs) {
  volatile VALUE vdb = rb_ary_shift(vargs);
  volatile VALUE vrv = rb_funcall(vdb, id_db_close, 0);
  if (vrv != Qtrue) rb_ary_push(vargs, rb_funcall(vdb, id_db_error, 0));
  return Qnil;
}


}


// END OF FILE
