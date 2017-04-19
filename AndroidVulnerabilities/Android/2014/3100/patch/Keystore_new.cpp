
ResponseCode getKeyForName(Blob* keyBlob, const android::String8& keyName, const uid_t uid, const BlobType type) {


android::String8 filepath8(getKeyNameForUidWithDir(keyName, uid));
}

android::String8 getKeyNameForUidWithDir(const android::String8& keyName, uid_t uid) {
    char encoded[encode_key_length(keyName) + 1]; // add 1 for null
    char encode_key(encoded, keyName);
return android::String8::format("%s/%u_%s", getUserState(uid)->getUserDirName(), uid,encoded);
}



static int encode_key( char* out, const android::String8& keyName)
{
  const uint8_t* in = reinterpret_cast(keyName.string());
  size_t length = keyName.length();
  for (int i = length; i > 0; --i, ++in, ++out)
  {
     if (*in < '0' || *in > '~')
     {
        *out = '+' + (*in >> 6);
        *++out = '0' + (*in & 0x3F);
        ++length;
     }
     else
     {
        *out = *in;
     }
  }
  *out = '';
  return length;
}