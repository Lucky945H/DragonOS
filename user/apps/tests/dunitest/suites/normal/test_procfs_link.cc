#include <gtest/gtest.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <cstdio>

class ProcfsLinkTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // 确保测试开始前目标文件不存在
        unlink(TEST_LINK);
    }

    void TearDown() override
    {
        // 测试结束后清理
        unlink(TEST_LINK);
    }

    static constexpr const char *PROC_SOURCE = "/proc/self/status";
    static constexpr const char *TEST_LINK = "/proc/self/status2";
};

TEST_F(ProcfsLinkTest, LinkToProcFileReturnsEPERM)
{
    // 尝试创建硬链接到 procfs 文件
    int ret = link(PROC_SOURCE, TEST_LINK);

    // 断言1: 返回值必须是 -1
    EXPECT_EQ(-1, ret);

    // 断言2: errno 必须是 EPERM
    EXPECT_EQ(EPERM, errno);

    // 断言3: 目标文件不应该被创建
    EXPECT_NE(0, access(TEST_LINK, F_OK));
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}