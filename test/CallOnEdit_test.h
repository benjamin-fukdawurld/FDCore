#ifndef CALLONEDIT_TEST_H
#define CALLONEDIT_TEST_H

#include <gtest/gtest.h>

#include <FDCore/CallOnEdit.h>


class FDCore_CallOnEdit : public ::testing::Test
{
    public:
        size_t editCount;

    public:
        ~FDCore_CallOnEdit() override = default;

        void SetUp() override;

        void onEdit(FDCore_CallOnEdit&);
        void onEditWithArg(size_t val, FDCore_CallOnEdit&);
};

void FDCore_CallOnEdit::SetUp()
{
    editCount = 0;
}

void FDCore_CallOnEdit::onEdit(FDCore_CallOnEdit&) { ++editCount; }
void FDCore_CallOnEdit::onEditWithArg(size_t val, FDCore_CallOnEdit&) { editCount += val; }

static size_t staticCounter = 0;

inline static void incrementStaticcounter(int &) { ++staticCounter; }
inline static void incrementStaticcounterWithArg(size_t val, int &) { staticCounter += val; }

inline static void incrementStaticcounterForObj(FDCore_CallOnEdit &) { ++staticCounter; }
inline static void incrementStaticcounterForObjWithArg(size_t val, FDCore_CallOnEdit &) { staticCounter += val; }

TEST_F(FDCore_CallOnEdit, StaticFunctions)
{
    {
        int val = 0;
        FDCore::CallOnEdit<int> coe(&val, &incrementStaticcounter);
        int *p = coe.getManagedObject();
        *p += 1;
        ASSERT_EQ(staticCounter, 1u);
        ASSERT_EQ(val, 1);
    }

    {
        int val = 0;
        const FDCore::CallOnEdit<int> coe(&val, &incrementStaticcounter);
        const int *p = coe.getManagedObject();
        ASSERT_EQ(staticCounter, 1u);
        ASSERT_EQ(*p, 0);
    }

    {
        int val = 0;
        size_t tmp = 3;
        FDCore::CallOnEdit<int> coe(&val, &incrementStaticcounterWithArg, tmp);
        int *p = coe.getManagedObject();
        *p += 1;
        ASSERT_EQ(staticCounter, 4u);
        ASSERT_EQ(val, 1);
    }

    {
        int val = 0;
        size_t tmp = 3;
        const FDCore::CallOnEdit<int> coe(&val, &incrementStaticcounterWithArg, tmp);
        const int *p = coe.getManagedObject();
        ASSERT_EQ(staticCounter, 4u);
        ASSERT_EQ(*p, 0);
    }
}

TEST_F(FDCore_CallOnEdit, lambdaFunctions)
{
    {
        int val = 0;
        FDCore::CallOnEdit<int> coe(&val, [](int &val) { val += 1; });
        int *p = coe.getManagedObject();
        ASSERT_EQ(val, 1);
        *p -= 1;
        ASSERT_EQ(val, 0);
    }

    {
        int val = 0;
        const FDCore::CallOnEdit<int> coe(&val, [](int &val) { val += 1; });
        const int *p = coe.getManagedObject();
        ASSERT_EQ(val, 0);
        ASSERT_EQ(*p, 0);
    }

    {
        int val = 0;
        int tmp = 3;
        FDCore::CallOnEdit<int> coe(&val, [](int s, int &val) { val += s; }, tmp);
        int *p = coe.getManagedObject();
        ASSERT_EQ(val, 3);
        *p -= 3;
        ASSERT_EQ(val, 0);
    }

    {
        int val = 0;
        int tmp = 3;
        const FDCore::CallOnEdit<int> coe(&val, [](int s, int &val) { val += s; }, tmp);
        const int *p = coe.getManagedObject();
        ASSERT_EQ(val, 0);
        ASSERT_EQ(*p, 0);
    }
}

TEST_F(FDCore_CallOnEdit, memberFunctions)
{
    {
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEdit, this);
        FDCore_CallOnEdit *p = coe.getManagedObject();
        ASSERT_EQ(editCount, 1u);
        p->editCount -= 1;
        ASSERT_EQ(editCount, 0u);
    }

    {
        const FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEdit, this);
        const FDCore_CallOnEdit *p = coe.getManagedObject();
        ASSERT_EQ(editCount, 0u);
        ASSERT_EQ(p->editCount, 0u);
    }

    {
        size_t tmp = 3u;
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEditWithArg, this, tmp);
        FDCore_CallOnEdit *p = coe.getManagedObject();
        ASSERT_EQ(editCount, 3u);
        p->editCount -= 3u;
        ASSERT_EQ(editCount, 0u);
    }

    {
        size_t tmp = 3u;
        const FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEditWithArg, this, tmp);
        const FDCore_CallOnEdit *p = coe.getManagedObject();
        ASSERT_EQ(editCount, 0u);
        ASSERT_EQ(p->editCount, 0u);
    }
}

TEST_F(FDCore_CallOnEdit, Constructors)
{
    {
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe;
        ASSERT_EQ(coe.getManagedObject(), nullptr);
        ASSERT_FALSE(coe.getCallback());
    }

    {
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this);
        ASSERT_EQ(coe.getManagedObject(), this);
        ASSERT_FALSE(coe.getCallback());
    }

    {
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEdit, this);
        ASSERT_TRUE(coe.getCallback());
        ASSERT_EQ(coe.getManagedObject(), this);
        ASSERT_EQ(editCount, 1u);
        editCount = 0;
    }

    {
        size_t tmp = 3;
        FDCore::CallOnEdit<FDCore_CallOnEdit> coe(this, &FDCore_CallOnEdit::onEditWithArg, this, tmp);
        ASSERT_TRUE(coe.getCallback());
        ASSERT_EQ(coe.getManagedObject(), this);
        ASSERT_EQ(editCount, 3u);
        editCount = 0;
    }
}

TEST_F(FDCore_CallOnEdit, Setters)
{
    FDCore::CallOnEdit<FDCore_CallOnEdit> coe;
    ASSERT_EQ(coe.getManagedObject(), nullptr);
    ASSERT_FALSE(coe.getCallback());

    {
        coe.setManagedObject(this);
        ASSERT_EQ(coe.getManagedObject(), this);
    }


    staticCounter = 0;
    {
        coe.setCallback(&incrementStaticcounterForObj);
        coe.getManagedObject();
        ASSERT_EQ(staticCounter, 1u);
    }

    {
        size_t tmp = 3;
        coe.setCallback(&incrementStaticcounterForObjWithArg, tmp);
        coe.getManagedObject();
        ASSERT_EQ(staticCounter, 4u);
    }

    {
        size_t val = 0;
        coe.setCallback([&val](FDCore_CallOnEdit&) { ++val; });
        coe.getManagedObject();
        ASSERT_EQ(val, 1u);
    }

    {
        size_t val = 0;
        size_t tmp = 3;
        coe.setCallback([&val](size_t s, FDCore_CallOnEdit&) { val += s; }, tmp);
        coe.getManagedObject();
        ASSERT_EQ(val, 3u);
        editCount = 0;
    }

    {
        coe.setCallback(&FDCore_CallOnEdit::onEdit, this);
        ASSERT_TRUE(coe.getCallback());
        ASSERT_EQ(coe.getManagedObject(), this);
        ASSERT_EQ(editCount, 1u);
        editCount = 0;
    }

    {
        size_t tmp = 3;
        coe.setCallback(&FDCore_CallOnEdit::onEditWithArg, this, tmp);
        coe.getManagedObject();
        ASSERT_EQ(editCount, 3u);
    }
}


#endif // CALLONEDIT_TEST_H
