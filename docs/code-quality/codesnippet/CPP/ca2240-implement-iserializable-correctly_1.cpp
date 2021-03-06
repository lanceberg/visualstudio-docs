using namespace System;
using namespace System::Security::Permissions;
using namespace System::Runtime::Serialization;

namespace Samples1 
{
    // Violates this rule
    [Serializable]
    public ref class Book : ISerializable
	{
    private:
        initonly String^ _Title;

    public: 
        Book(String^ title)
        {
            if (title == nullptr)
                throw gcnew ArgumentNullException("title");

            _Title = title;
        }

        property String^ Title
        {
            String^ get()
            {
                return _Title;
            }
        }

    protected: 
        Book(SerializationInfo^ info, StreamingContext context)
        {
            if (info == nullptr)
                throw gcnew ArgumentNullException("info");

            _Title = info->GetString("Title");
        }

    private:
        [SecurityPermission(SecurityAction::LinkDemand, Flags = SecurityPermissionFlag::SerializationFormatter)]
        void virtual GetObjectData(SerializationInfo^ info, StreamingContext context) sealed = ISerializable::GetObjectData
        {
            if (info == nullptr)
                throw gcnew ArgumentNullException("info");

            info->AddValue("Title", _Title);
        }
	};

    // Violates this rule
    [Serializable]
    public ref class LibraryBook : Book
    {
        initonly DateTime _CheckedOut;

    public:
        LibraryBook(String^ title, DateTime checkedOut) : Book(title)
        {
            _CheckedOut = checkedOut;
        }
        
        property DateTime CheckedOut
        {
            DateTime get()
            {
                return _CheckedOut;
            }
        }
    };
}