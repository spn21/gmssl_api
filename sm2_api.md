宏：

1. **`SM2_DEFAULT_ID`**
   - 默认的 SM2 用户标识符。用户标识符通常是用户的身份信息或者其他标识信息。
2. **`SM2_MAX_ID_LENGTH`**
   - SM2 用户标识符的最大长度。这限制了用户标识符的最大长度确保能够被正确处理。
3. **`SM2_MAX_SIGNATURE_SIZE`**
   - SM2 签名的最大长度。SM2 签名生成的字节长度上限。
4. **`SM2_MAX_PLAINTEXT_SIZE`**
   - SM2 加密前数据的最大长度。 SM2 加密前明文数据的字节长度上限。
5. **`SM2_MAX_CIPHERTEXT_SIZE`**
   - SM2 加密后数据（密文）的最大长度。SM2 加密后密文数据的字节长度上限。



1. **`sm2_key_generate`**

   - 生成新的 SM2 密钥对（公私钥对）。

   ```c++
   int sm2_key_generate(SM2_KEY *sm2_key);
   ```

2. **`sm2_private_key_info_encrypt_to_der`**

   - 对私钥信息进行加密，并将其导出为 DER

   ```c++
   int sm2_private_key_info_encrypt_to_der(const SM2_KEY *sm2_key, const char *password, unsigned char *out, size_t *outlen);
   ```

3. **`sm2_private_key_info_decrypt_from_der`**

   - 从 DER 格式中解密私钥信息。

   ```c++
   int sm2_private_key_info_decrypt_from_der(SM2_KEY *sm2_key, const char *password, const unsigned char *in, size_t inlen);
   ```

4. **`sm2_private_key_info_encrypt_to_pem`**

   - 私钥信息加密，并将其导出为 PEM

   ```c++
   int sm2_private_key_info_encrypt_to_pem(const SM2_KEY *sm2_key, const char *password, FILE *fp);
   ```

5. **`sm2_private_key_info_decrypt_from_pem`**

   - 从 PEM 中解密私钥信息。

   ```c++
   int sm2_private_key_info_decrypt_from_pem(SM2_KEY *sm2_key, const char *password, FILE *fp);
   ```

6. **`sm2_public_key_info_to_der`**

   - 将公钥信息导出为 DER 。

   ```c++
   int sm2_public_key_info_to_der(const SM2_KEY *sm2_key, unsigned char *out, size_t *outlen);
   ```

7. **`sm2_public_key_info_from_der`**

   - 从 DER 中导入公钥信息。

   ```c++
   int sm2_public_key_info_from_der(SM2_KEY *sm2_key, const unsigned char *in, size_t inlen);
   ```

8. **`sm2_public_key_info_to_pem`**

   - 将公钥信息导出为 PEM 。

   ```c++
   int sm2_public_key_info_to_pem(const SM2_KEY *sm2_key, FILE *fp);
   ```

9. **`sm2_public_key_info_from_pem`**

   - 从 PEM中导入公钥

   ```c++
   int sm2_public_key_info_from_pem(SM2_KEY *sm2_key, FILE *fp);
   ```

1. **`sm2_sign`**

   - 私钥对消息签名。

   ```c++
   int sm2_sign(const SM2_KEY *sm2_key, const unsigned char *dgst, unsigned char *sig, size_t *siglen);
   ```

   

   ```c++
   SM2_KEY sm2_key;
   unsigned char dgst[32];  // 消息摘要
   unsigned char sig[SM2_MAX_SIGNATURE_SIZE];
   size_t siglen;
   
   // 签名
   if (sm2_sign(&sm2_key, dgst, sig, &siglen) != 1) {
       fprintf(stderr, "Error in signing\n");
   }
   ```

2. **`sm2_verify`**

   - 用公钥验证消息签名。

   ```c++
   int sm2_verify(const SM2_KEY *sm2_key, const unsigned char *dgst, const unsigned char *sig, size_t siglen);
   ```

   ```c
   SM2_KEY pub_key;
   unsigned char dgst[32];  // 消息摘要
   unsigned char sig[SM2_MAX_SIGNATURE_SIZE];
   size_t siglen;
   
   // 验证签名
   if (sm2_verify(&pub_key, dgst, sig, siglen) != 1) {
       fprintf(stderr, "Verification failed\n");
   }
   ```

**`sm2_encrypt`**

- 使用公钥加密数据。

```c++
int sm2_encrypt(const SM2_KEY *sm2_key, const unsigned char *plaintext, size_t plaintext_len, unsigned char *ciphertext, size_t *ciphertext_len);
```

```c++
SM2_KEY pub_key;
unsigned char plaintext[128];  // 待加密的数据
unsigned char ciphertext[SM2_MAX_CIPHERTEXT_SIZE];
size_t ciphertext_len;

// 加密
if (sm2_encrypt(&pub_key, plaintext, sizeof(plaintext), ciphertext, &ciphertext_len) != 1) {
    fprintf(stderr, "Encryption failed\n");
}
```

**`sm2_decrypt`**

- 使用私钥解密数据。

```c++
int sm2_decrypt(const SM2_KEY *sm2_key, const unsigned char *ciphertext, size_t ciphertext_len, unsigned char *plaintext, size_t *plaintext_len);
```

```c++
SM2_KEY sm2_key;
unsigned char ciphertext[SM2_MAX_CIPHERTEXT_SIZE];  // 加密后的数据
unsigned char plaintext[128];
size_t plaintext_len;

// 解密
if (sm2_decrypt(&sm2_key, ciphertext, sizeof(ciphertext), plaintext, &plaintext_len) != 1) {
    fprintf(stderr, "Decryption failed\n");
}
```



**`SM2_SIGN_CTX`**

- SM2 签名上下文结构。

```c++
typedef struct {
    SM2_KEY *sm2_key;
    // 其他上下文数据
} SM2_SIGN_CTX;
```

1. **`sm2_sign_init`**

   - 初始化 SM2 签名上下文。

   ```c++
   void sm2_sign_init(SM2_SIGN_CTX *ctx, const SM2_KEY *sm2_key);
   ```

2. **`sm2_sign_update`**

   - 更新 SM2 签名上下文。

   ```c++
   void sm2_sign_update(SM2_SIGN_CTX *ctx, const unsigned char *dgst, size_t dgstlen);
   ```

3. **`sm2_sign_finish`**

   - 完成 SM2 签名。

   ```c++
   int sm2_sign_finish(SM2_SIGN_CTX *ctx, unsigned char *sig, size_t *siglen);
   ```

   