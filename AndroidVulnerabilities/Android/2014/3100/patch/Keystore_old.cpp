ResponseCode getKeyForName( Blob* keyBlob,
                            const android::String8& keyName,
                            const uid_t uid,
                            const BlobType type)
{
  char filename[NAME_MAX];
  encode_key_for_uid(filename, uid, keyName);
...
}
static int encode_key_for_uid( char* out,
                               uid_t uid,
                               const android::String8& keyName)
{
  int n = snprintf(out, NAME_MAX, "%u_", uid);
  out += n; return n + encode_key(out, keyName);
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