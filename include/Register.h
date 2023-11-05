#ifndef REGISTER_H
#define REGISTER_H


class Register
{
    public:
        Register();
        virtual ~Register();
        void increase(bool signal);
        void load(int dataBus, bool signal);
        void output(int& dataBus, bool signal);
        int getData();

    private:
        int data;
};

#endif // REGISTER_H
