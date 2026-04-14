#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#define PROC_SOURCE "/proc/self/status"
#define TEST_LINK   "/proc/self/status2"

int main(void) {
    int ret;
    int errno_saved;

    printf("=== procfs link() regression test ===\n");
    printf("Testing: link(\"%s\", \"%s\")\n", PROC_SOURCE, TEST_LINK);

    /* 确保目标文件不存在 */
    unlink(TEST_LINK);

    /* 尝试创建硬链接到 procfs 文件 */
    ret = link(PROC_SOURCE, TEST_LINK);
    errno_saved = errno;

    /* 断言1: 返回值必须是 -1 */
    if (ret != -1) {
        fprintf(stderr, "FAIL: link() returned %d, expected -1\n", ret);
        exit(1);
    }
    printf("PASS: link() returned -1\n");

    /* 断言2: errno 必须是 EPERM (Linux 标准行为) */
    if (errno_saved != EPERM) {
        fprintf(stderr, "FAIL: expected errno=EPERM(%d), got errno=%d (%s)\n",
                EPERM, errno_saved, strerror(errno_saved));
        exit(1);
    }
    printf("PASS: errno = EPERM (%d) as expected\n", errno_saved);

    /* 验证没有创建文件 */
    if (access(TEST_LINK, F_OK) == 0) {
        fprintf(stderr, "FAIL: link unexpectedly created file %s\n", TEST_LINK);
        exit(1);
    }
    printf("PASS: target file not created\n");

    /* 清理 */
    unlink(TEST_LINK);

    printf("=== All tests passed ===\n");
    return 0;
}