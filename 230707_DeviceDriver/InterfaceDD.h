class IDeviceDriver
{
public:
    virtual int read(long address) = 0;
    virtual void write(long address, int data) = 0;
};