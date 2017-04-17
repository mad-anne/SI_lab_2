//
// Created by Anna Siwik on 2017-04-15.
//

#ifndef SI_LAB_2_IROW_H
#define SI_LAB_2_IROW_H

#include <components/interface/IValue.h>
#include <vector>

class IRow
{
    protected:
        std::vector<const IValue*> values;
        int width;

    public:
        IRow(int width) :
            width(width)
        {}
        virtual ~IRow()
        {}

        virtual bool compareWith(const IRow* row) const
        {
            if (width != row->width)
                return false;

            for (int index = 0; index < width; ++index)
            {
                if (values[index] != row->values[index])
                    return false;
            }

            return true;
        };

        virtual bool compareWithAllowingNulls(const IRow* row) const
        {
            if (width != row->width)
                return false;

            for (int index = 0; index < width; ++index)
            {
                if (values[index] != row->values[index] && values[index] != nullptr && row->values[index] != nullptr)
                    return false;
            }

            return true;
        };

        virtual const IValue* getValue(int index) const
        {
            return  (index < 0 || index >= values.size())
                    ? nullptr
                    : values[index];
        }

        virtual int getWidth() const
        {
            return width;
        }

        virtual int countValue(const IValue* value) const
        {
            int counter = 0;

            for (int index = 0; index < width; ++index)
            {
                if (values[index] == value)
                    ++counter;
            }

            return counter;
        }

        virtual bool isCompleted() const
        {
            for (int index = 0; index < width; ++index)
            {
                if (values[index] == nullptr)
                    return false;
            }

            return true;
        }

        virtual bool isCorrect() const
        {
            for (int index = 2; index < width; ++index)
            {
                const IValue* first = values[index - 2];
                const IValue* second = values[index - 1];
                const IValue* third = values[index];

                if (first == second && second == third
                    && first != nullptr && second != nullptr && third != nullptr)
                {
                    return false;
                }
            }

            return true;
        }

        virtual const IValue* getValueAfterPair(unsigned long int index)
        {
            return (index < 0 || index >= values.size())
                    ? nullptr
                    : values[index];
        }
};

#endif //SI_LAB_2_IROW_H
