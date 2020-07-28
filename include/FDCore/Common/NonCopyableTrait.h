#ifndef FDCORE_NONCOPYABLETRAIT_H
#define FDCORE_NONCOPYABLETRAIT_H

namespace FDCore
{
    class NonCopyable
    {
      public:
        NonCopyable() = default;
        virtual ~NonCopyable() = default;

      private:
        NonCopyable(const NonCopyable &) = delete;
        NonCopyable &operator=(const NonCopyable &) = delete;
    };

    class NonMovable
    {
      public:
        NonMovable() = default;
        virtual ~NonMovable() = default;

      private:
        NonMovable(NonMovable &&) = delete;
        NonMovable &operator=(NonMovable &&) = delete;
    };
} // namespace FDCore

#endif // FDCORE_NONCOPYABLETRAIT_H
