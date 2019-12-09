#ifndef ENUMFLAG_H
#define ENUMFLAG_H

namespace FDCore
{
    template<typename EnumType, typename StorageType = int>
    class EnumFlag
    {
        private:
            class FlagProxy
            {
                friend class EnumFlag<EnumType, StorageType>;
                private:
                    EnumFlag<EnumType, StorageType> &m_flags;
                    EnumType m_value;

                    FlagProxy(EnumFlag<EnumType, StorageType> &flags, EnumType value) :
                        m_flags(flags),
                        m_value(value)
                    {}

                public:
                    FlagProxy &operator=(bool toggle)
                    {
                        if(toggle)
                            m_flags |= m_value;
                        else
                            m_flags -= m_value;

                        return *this;
                    }

                    operator bool() const { return m_flags.operator==(m_value); }
            };

        protected:
            StorageType m_value;

        public:
            EnumFlag() :
                m_value(0)
            {}

            EnumFlag(EnumType type) :
                m_value(static_cast<StorageType>(type))
            {}

            EnumFlag(StorageType flags) :
                m_value(flags)
            {}

            operator StorageType() const { return m_value; }

            EnumFlag &operator|=(EnumType type)
            {
                m_value |= static_cast<StorageType>(type);
                return *this;
            }

            EnumFlag &operator|=(StorageType flag)
            {
                m_value |= flag;
                return *this;
            }

            EnumFlag operator|(EnumType type) const
            {
                return EnumFlag(m_value | static_cast<StorageType>(type));
            }

            EnumFlag operator|(StorageType flag) const
            {
                return EnumFlag(m_value | flag);
            }

            EnumFlag &operator&=(EnumType type)
            {
                m_value &= static_cast<StorageType>(type);
                return *this;
            }

            EnumFlag &operator&=(StorageType flag)
            {
                m_value &= flag;
                return *this;
            }

            EnumFlag operator&(EnumType type) const
            {
                return EnumFlag(m_value & static_cast<StorageType>(type));
            }

            EnumFlag operator&(StorageType flag) const
            {
                return EnumFlag(m_value & flag);
            }

            EnumFlag &operator^=(EnumType type)
            {
                m_value ^= static_cast<StorageType>(type);
                return *this;
            }

            EnumFlag &operator^=(StorageType flag)
            {
                m_value ^= flag;
                return *this;
            }

            EnumFlag operator^(EnumType type) const
            {
                return EnumFlag(m_value ^ static_cast<StorageType>(type));
            }

            EnumFlag operator^(StorageType flag) const
            {
                return EnumFlag(m_value ^ flag);
            }

            EnumFlag &operator-=(EnumType type)
            {
                return *this &= ~static_cast<StorageType>(type);
            }

            EnumFlag &operator-=(StorageType flag)
            {
                return *this &= ~static_cast<StorageType>(flag);
            }

            EnumFlag operator~() const
            {
                return EnumFlag(~m_value);
            }

            bool operator==(EnumType type) const
            {
                return m_value == static_cast<StorageType>(type);
            }

            bool operator==(StorageType flag) const
            {
                return m_value == flag;
            }

            FlagProxy operator[](EnumType type)
            {
                return FlagProxy(*this, type);
            }

            bool operator[](EnumType type) const
            {
                return (m_value & static_cast<StorageType>(type)) != 0;
            }

            bool operator[](StorageType flag) const
            {
                return (m_value & flag) == flag;
            }
    };

}

#endif // ENUMFLAG_H
