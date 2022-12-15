__int64 __fastcall Srv2DecompressData(__int64 a1)
{
  __int64 v2; // rax
  __m128i v3; // xmm0
  unsigned int v4; // ebp
  __int64 Buffer; // rax
  __int64 v7; // rbx
  int v8; // eax
  __m128i Size; // [rsp+30h] [rbp-28h]
  int v10; // [rsp+60h] [rbp+8h] BYREF

  v10 = 0;
  v2 = *(_QWORD *)(a1 + 0xF0);
  if ( *(_DWORD *)(v2 + 0x24) < 0x10u )
    return 0xC000090Bi64;
  Size = *(__m128i *)*(_QWORD *)(v2 + 0x18);
  v3 = _mm_srli_si128(Size, 8);
  v4 = *(_DWORD *)(*(_QWORD *)(*(_QWORD *)(a1 + 0x50) + 0x1F0i64) + 0x8Ci64);
  if ( v4 != v3.m128i_u16[0] )
    return 0xC00000BBi64;
  Buffer = SrvNetAllocateBuffer((unsigned int)(Size.m128i_i32[1] + v3.m128i_i32[1]), 0i64);
  v7 = Buffer;
  if ( !Buffer )
    return 0xC000009Ai64;
  if ( (int)SmbCompressionDecompress(
              v4,
              *(_QWORD *)(*(_QWORD *)(a1 + 0xF0) + 0x18i64) + Size.m128i_u32[3] + 0x10i64,
              (unsigned int)(*(_DWORD *)(*(_QWORD *)(a1 + 0xF0) + 0x24i64) - Size.m128i_i32[3] - 0x10),
              Size.m128i_u32[3] + *(_QWORD *)(Buffer + 0x18),
              Size.m128i_i32[1],
              &v10) < 0
    || (v8 = v10, v10 != Size.m128i_i32[1]) )
  {
    SrvNetFreeBuffer(v7);
    return 0xC000090Bi64;
  }
  if ( Size.m128i_i32[3] )
  {
    memmove(
      *(void **)(v7 + 0x18),
      (const void *)(*(_QWORD *)(*(_QWORD *)(a1 + 0xF0) + 0x18i64) + 0x10i64),
      Size.m128i_u32[3]);
    v8 = v10;
  }
  *(_DWORD *)(v7 + 36) = Size.m128i_i32[3] + v8;
  Srv2ReplaceReceiveBuffer(a1, v7);
  return 0i64;
}
