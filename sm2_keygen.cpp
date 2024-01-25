//
// Created by mouzi on 2024/1/25.
//
/*
 *  版权所有 2014-2023 The GmSSL Project。保留所有权利。
 *
 *  根据 Apache 许可证 2.0 版（许可证）获得许可；除非符合许可证，否则您不得
 *  使用此文件。
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmssl/sm2.h>

int main(void)
{
    // 定义一个 SM2_KEY 结构体，用于保存生成的密钥对
    SM2_KEY sm2_key;

    // 生成 SM2 密钥对
    if (sm2_key_generate(&sm2_key) != 1) {
        fprintf(stderr, "生成密钥对时发生错误\n");
        return 1;
    }

    // 打印生成的私钥信息到标准输出
    // 参数说明：
    //   - stdout: 输出到标准输出
    //   - 0: 不使用 PEM 格式
    //   - 0: 不使用密码加密私钥
    //   - "SM2PrivateKey": 打印信息的前缀
    //   - &sm2_key: 要打印的私钥结构体
    sm2_key_print(stdout, 1, 0, "SM2PrivateKey", &sm2_key);

    // 打印生成的公钥信息到标准输出
    // 参数说明：
    //   - stdout: 输出到标准输出
    //   - 0: 不使用 PEM 格式
    //   - 0: 不使用密码加密公钥
    //   - "SM2PublicKey": 打印信息的前缀
    //   - &sm2_key: 要打印的公钥结构体
    sm2_public_key_print(stdout, 0, 0, "SM2PublicKey", &sm2_key);

    return 0;
}