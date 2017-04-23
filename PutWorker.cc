#include <nan.h>
#include "PutWorker.h"  
#include "rocksdb/db.h"

PutWorker::PutWorker(Nan::Callback *callback, rocksdb::DB *db, rocksdb::Slice key, rocksdb::Slice value, rocksdb::WriteOptions options)
    : AsyncWorker(callback), _db(db), _key(key), _value(value), _options(options) {}
PutWorker::~PutWorker() {}

void PutWorker::Execute () {
  _status = _db->Put(_options, _key, _value);
}
void PutWorker::HandleOKCallback () {
  Nan::HandleScope scope;
  
  v8::Local<v8::Value> argv[1] = { Nan::Null() };
  if (!_status.ok()) {
    argv[0] = Nan::New<v8::String>(_status.getState()).ToLocalChecked();
  } 
  callback->Call(1, argv);
}
