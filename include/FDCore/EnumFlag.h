#ifndef ENUMFLAG_H
#define ENUMFLAG_H

namespace FDCore
{
    /**
     * @brief EnumFlag is a wrapper class to allow user to use enum class as flags
     *
     * @tparam EnumType The enum to wrap
     * @tparam StorageType The storage type of the enum (default value is int)
     */
    template<typename EnumType, typename StorageType = int>
    class EnumFlag
    {
        private:
            /**
             * @brief FlagProxy is an access proxy class to simplify checking and setting of a given field in the flag
             *
             */
            class FlagProxy
            {
                friend class EnumFlag<EnumType, StorageType>;
                private:
                    EnumFlag<EnumType, StorageType> &m_flags; ///< The EnumFlag object wrapped by this proxy
                    EnumType m_value; ///< The value of the field to manage

                    /**
                     * @brief Constructs a new Flag Proxy object
                     *
                     * @param flags The EnumFlag object wrapped by this proxy
                     * @param value The value of the field to manage
                     */
                    FlagProxy(EnumFlag<EnumType, StorageType> &flags, EnumType value) :
                        m_flags(flags),
                        m_value(value)
                    {}

                public:

                    /**
                     * @brief Sets the status of the field (activated/disactivated)
                     *
                     * @param activated The status to set to the field
                     * @return a reference to this object
                     */
                    FlagProxy &operator=(bool activated)
                    {
                        if(activated)
                            m_flags |= m_value;
                        else
                            m_flags -= m_value;

                        return *this;
                    }

                    /**
                     * @brief Checks whether this field is activated or not
                     *
                     * @return true if the field is acctivated, false otherwise
                     */
                    operator bool() const { return m_flags.operator&(m_value); }
            };

        protected:
            StorageType m_value; ///< The storage of the flags fields

        public:
            /**
             * @brief Constructs a new Enum Flag object with all fields disactivated
             */
            EnumFlag() :
                m_value(0)
            {}

            /**
             * @brief Constructs a new Enum Flag object with the field @b type activated
             *
             * @param type The field to activate
             */
            EnumFlag(EnumType type) :
                m_value(static_cast<StorageType>(type))
            {}

            /**
             * @brief Constructs a new Enum Flag object with a the value of the param @b flags
             *
             * @param flags the value to initialize the flags with
             */
            EnumFlag(StorageType flags) :
                m_value(flags)
            {}

            /**
             * @brief Converts the Enum flag into its storage type implicitly
             *
             * @return StorageType the flags value as StorageType
             */
            operator StorageType() const { return m_value; }

            /**
             * @brief Activates a field
             *
             * @param type The field to activate
             * @return A reference to this object
             */
            EnumFlag<EnumType, StorageType> &operator|=(EnumType type)
            {
                m_value |= static_cast<StorageType>(type);
                return *this;
            }

            /**
             * @brief Activates fields from flag
             *
             * @param flag The fields to activate
             * @return A reference to this object
             */
            EnumFlag<EnumType, StorageType> &operator|=(StorageType flag)
            {
                m_value |= flag;
                return *this;
            }

            /**
             * @brief Activates a field
             *
             * @param type The field to activate
             * @return A new EnumFlag
             */
            EnumFlag<EnumType, StorageType> operator|(EnumType type) const
            {
                return EnumFlag<EnumType, StorageType>(m_value | static_cast<StorageType>(type));
            }

            /**
             * @brief Activates fields from flag
             *
             * @param flag The fields to activate
             * @return A new EnumFlag
             */
            EnumFlag<EnumType, StorageType> operator|(StorageType flag) const
            {
                return EnumFlag<EnumType, StorageType>(m_value | flag);
            }

            EnumFlag<EnumType, StorageType> &operator&=(EnumType type)
            {
                m_value &= static_cast<StorageType>(type);
                return *this;
            }

            EnumFlag<EnumType, StorageType> &operator&=(StorageType flag)
            {
                m_value &= flag;
                return *this;
            }

            EnumFlag<EnumType, StorageType> operator&(EnumType type) const
            {
                return EnumFlag<EnumType, StorageType>(m_value & static_cast<StorageType>(type));
            }

            EnumFlag<EnumType, StorageType> operator&(StorageType flag) const
            {
                return EnumFlag<EnumType, StorageType>(m_value & flag);
            }

            EnumFlag<EnumType, StorageType> &operator^=(EnumType type)
            {
                m_value ^= static_cast<StorageType>(type);
                return *this;
            }

            EnumFlag<EnumType, StorageType> &operator^=(StorageType flag)
            {
                m_value ^= flag;
                return *this;
            }

            EnumFlag<EnumType, StorageType> operator^(EnumType type) const
            {
                return EnumFlag<EnumType, StorageType>(m_value ^ static_cast<StorageType>(type));
            }

            EnumFlag<EnumType, StorageType> operator^(StorageType flag) const
            {
                return EnumFlag<EnumType, StorageType>(m_value ^ flag);
            }

            EnumFlag<EnumType, StorageType> &operator-=(EnumType type)
            {
                return *this &= ~static_cast<StorageType>(type);
            }

            EnumFlag<EnumType, StorageType> &operator-=(StorageType flag)
            {
                return *this &= ~static_cast<StorageType>(flag);
            }

            EnumFlag<EnumType, StorageType> operator~() const
            {
                return EnumFlag<EnumType, StorageType>(~m_value);
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
                return (m_value & static_cast<StorageType>(type)) == static_cast<StorageType>(type);
            }

            bool operator[](StorageType flag) const
            {
                return (m_value & flag) == flag;
            }
    };

}

#endif // ENUMFLAG_H
