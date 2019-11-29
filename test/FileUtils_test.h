#ifndef FILEUTILS_TEST_H
#define FILEUTILS_TEST_H

#include <gtest/gtest.h>

#include <FDCore/FileUtils.h>

#include <fstream>
#include <sstream>
#include <limits>

class FDCore_FileUtils_readFile : public ::testing::Test
{
    protected:
        std::streambuf *m_stdErrStream;
        std::stringstream m_errBuffer;

    public:
        ~FDCore_FileUtils_readFile() override;

    protected:
        static constexpr const char *getLoremIpsum()
        {
            return R"testText(Sed ut tum ad senem senex de senectute, sic hoc libro ad amicum
    amicissimus scripsi de amicitia. Tum est Cato locutus, quo erat nemo fere senior
    temporibus illis, nemo prudentior; nunc Laelius et sapiens (sic enim est habitus) et
    amicitiae gloria excellens de amicitia loquetur. Tu velim a me animum parumper
    avertas, Laelium loqui ipsum putes. C. Fannius et Q. Mucius ad socerum veniunt post
    mortem Africani; ab his sermo oritur, respondet Laelius, cuius tota disputatio est de
    amicitia, quam legens te ipse cognosces.)testText";
        }

        static constexpr const char *getTextFilePath()
        {
            return "text_file.txt";
        }

        static constexpr const char *getEmptyFilePath()
        {
            return "empty_file.txt";
        }

        static constexpr const char *getNoFilePath()
        {
            return "no_file";
        }

        void SetUp() override
        {
            std::ofstream f;
            f.open(getTextFilePath());
            if(!f.is_open())
                throw std::runtime_error("unable to open text file");

            f << getLoremIpsum();

            f.close();

            f.open(getEmptyFilePath());
            if(!f.is_open())
                throw std::runtime_error("unable to open empty file");
            f.close();

            m_stdErrStream = std::cout.rdbuf();
            std::cout.rdbuf(m_errBuffer.rdbuf());
        }

        void TearDown() override
        {
            std::cerr.rdbuf(m_stdErrStream);

            if(remove(getTextFilePath()) != 0)
                throw std::runtime_error("unable to delete text file");

            if(remove(getEmptyFilePath()) != 0)
                throw std::runtime_error("unable to delete empty file");
        }
};

FDCore_FileUtils_readFile::~FDCore_FileUtils_readFile(){}

class FDCore_FileUtils_readBinaryFile : public ::testing::Test
{
    protected:
        std::streambuf *m_stdErrStream;
        std::stringstream m_errBuffer;

    public:
        ~FDCore_FileUtils_readBinaryFile() override;

    protected:
        struct TestStruct
        {
            int i;
            float f;
            double d;
            bool b;
            char c;

            TestStruct(int i, float f, double d, bool b, char c) :
                i(i), f(f), d(d), b(b), c(c)
            {}

            bool operator==(const TestStruct &t) const
            {
                return i == t.i && std::abs(f - t.f) <= std::numeric_limits<float>::epsilon()
                    && std::abs(d - t.d) <= std::numeric_limits<double>::epsilon()
                    && b == t.b && c == t.c;
            }
        };

    protected:
        static TestStruct getTestStruct()
        {
            return { 42, 3.14f, 1.23456, true, 'a' };
        }

        static constexpr const char *getBinFilePath()
        {
            return "bin_file";
        }

        static constexpr const char *getEmptyFilePath()
        {
            return "empty_bin_file";
        }

        static constexpr const char *getNoFilePath()
        {
            return "no_file";
        }

        void SetUp() override
        {
            std::unique_ptr<FILE, decltype (&fclose)> f(fopen(getBinFilePath(), "wb"), &fclose);
            if(!f)
                throw std::runtime_error("unable to open bin file");

            TestStruct test = getTestStruct();

            if(fwrite(&test, sizeof(TestStruct), 1, f.get()) != 1)
                throw std::runtime_error("unable to write test data in bin file");

            f.reset(fopen(getEmptyFilePath(), "wb"));
            if(!f)
                throw std::runtime_error("unable to open empty file");

            m_stdErrStream = std::cout.rdbuf();
            std::cout.rdbuf(m_errBuffer.rdbuf());
        }

        void TearDown() override
        {
            std::cerr.rdbuf(m_stdErrStream);

            if(remove(getBinFilePath()) != 0)
                throw std::runtime_error("unable to delete text file");

            if(remove(getEmptyFilePath()) != 0)
                throw std::runtime_error("unable to delete empty file");
        }
};

FDCore_FileUtils_readBinaryFile::~FDCore_FileUtils_readBinaryFile(){}

TEST_F(FDCore_FileUtils_readFile, TextFileTest)
{
    std::unique_ptr<char[]> result = FDCore::readFile(FDCore_FileUtils_readFile::getTextFilePath());
    ASSERT_NE(result.get(), nullptr);
    ASSERT_STREQ(FDCore_FileUtils_readFile::getLoremIpsum(), result.get());
}

TEST_F(FDCore_FileUtils_readFile, readFile_EmptyFileTest)
{
    std::unique_ptr<char[]> result = FDCore::readFile(FDCore_FileUtils_readFile::getEmptyFilePath());
    ASSERT_EQ(result.get(), nullptr);
}

TEST_F(FDCore_FileUtils_readFile, readFile_nonExistingFileTest)
{
    std::unique_ptr<char[]> result = FDCore::readFile(FDCore_FileUtils_readFile::getNoFilePath());
    ASSERT_STREQ(m_errBuffer.str().c_str(), "The file descriptor is not set\n");
    ASSERT_EQ(result.get(), nullptr);
}

TEST_F(FDCore_FileUtils_readBinaryFile, TextFileTest)
{
    size_t s = 0;
    std::unique_ptr<uint8_t[]> result =
            FDCore::readBinaryFile(FDCore_FileUtils_readBinaryFile::getBinFilePath(), s);
    ASSERT_NE(result.get(), nullptr);
    ASSERT_EQ(s, sizeof(TestStruct));
    ASSERT_EQ(getTestStruct(), *reinterpret_cast<TestStruct*>(result.get()));
}

TEST_F(FDCore_FileUtils_readBinaryFile, readFile_EmptyFileTest)
{
    size_t s = 0;
    std::unique_ptr<uint8_t[]> result =
            FDCore::readBinaryFile(FDCore_FileUtils_readBinaryFile::getEmptyFilePath(), s);
    ASSERT_EQ(result.get(), nullptr);
}

TEST_F(FDCore_FileUtils_readBinaryFile, readFile_nonExistingFileTest)
{
    size_t s = 0;
    std::unique_ptr<uint8_t[]> result =
            FDCore::readBinaryFile(FDCore_FileUtils_readBinaryFile::getNoFilePath(), s);
    ASSERT_STREQ(m_errBuffer.str().c_str(), "The file descriptor is not set\n");
    ASSERT_EQ(result.get(), nullptr);
}

#endif // FILEUTILS_TEST_H
