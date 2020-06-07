#ifndef NONCOPYABLETRAIT_H
#define NONCOPYABLETRAIT_H

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

#endif // NONCOPYABLETRAIT_H
