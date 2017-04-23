#ifndef NODE_GYP_WRAPPER
#define NODE_GYP_WRAPPER

#include <utility>
#include <string>

#include <node.h>

namespace nw {
    namespace _detail {
        inline std::string to_string(const v8::Local<v8::String>& s)noexcept {
            v8::String::Utf8Value str(s);
            return *str;
        }
        inline std::string to_string(v8::Local<v8::String>&& s)noexcept {
            v8::String::Utf8Value str(s);
            return *str;
        }
        inline std::string to_string(const v8::Local<v8::Value>& s)noexcept {
            v8::String::Utf8Value str(s);
            return *str;
        }
        inline std::string to_string(v8::Local<v8::Value>&& s)noexcept {
            v8::String::Utf8Value str(s);
            return *str;
        }
    } /* _detail */
    class string {
    public:
        using iterator=typename std::string::iterator;
        using const_iterator=typename std::string::const_iterator;
        using reverse_iterator=typename std::string::reverse_iterator;
        using const_reverse_iterator=typename std::string::const_reverse_iterator;
    private:
        std::string m_str;
    public:
        string()=default;
        string(const string&)=default;
        string(string&&)=default;
    public:
        string(const std::string& s) : m_str(s) {}
        string(std::string&& s)noexcept : m_str(s) {}
    public:
        string(const char *s) : m_str(s) {}
    public:
        string(const v8::Local<v8::String>& s)noexcept : m_str(_detail::to_string(s)) {}
        string(v8::Local<v8::String>&& s)noexcept : m_str(_detail::to_string(s)) {}
    public:
        string& operator=(const string&)=default;
        string& operator=(string&&)=default;
    public:
        string& operator=(const std::string& s) {
            m_str=s;
            return *this;
        }
        string& operator=(std::string&& s)noexcept {
            m_str=s;
            return *this;
        }
    public:
        string& operator=(const v8::Local<v8::String>& s) {
            m_str=_detail::to_string(s);
            return *this;
        }
        string& operator=(v8::Local<v8::String>&& s) {
            m_str=_detail::to_string(s);
            return *this;
        }
    public:
        std::string& str() {
            return m_str;
        }
        std::string str()const {
            return m_str;
        }
        v8::Local<v8::String> v8_str()const {
            return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str().c_str());
        }
        const char* c_str()const {
            return m_str.c_str();
        }
    public:
        std::size_t size()const noexcept {
            return m_str.size();
        }
        std::size_t length()const noexcept {
            return m_str.length();
        }
        bool empty()const noexcept {
            return m_str.empty();
        }
        void clear()noexcept {
            m_str.clear();
        }
    public:
        iterator begin()noexcept {
            return m_str.begin();
        }
        iterator end()noexcept {
            return m_str.end();
        }
    public:
        const_iterator begin()const noexcept {
            return m_str.begin();
        }
        const_iterator end()const noexcept {
            return m_str.end();
        }
    public:
        const_iterator cbegin()const noexcept {
            return m_str.cbegin();
        }
        const_iterator cend()const noexcept {
            return m_str.cend();
        }
    public:
        reverse_iterator rbegin()noexcept {
            return m_str.rbegin();
        }
        reverse_iterator rend()noexcept {
            return m_str.rend();
        }
    public:
        const_reverse_iterator rbegin()const noexcept {
            return m_str.rbegin();
        }
        const_reverse_iterator rend()const noexcept {
            return m_str.rend();
        }
    public:
        const_reverse_iterator crbegin()const noexcept {
            return m_str.crbegin();
        }
        const_reverse_iterator crend()const noexcept {
            return m_str.crend();
        }
    public:
        string& operator+=(const string& s) {
            m_str+=s.str();
            return *this;
        }
        string& operator+=(const std::string& s) {
            m_str+=s;
            return *this;
        }
        string& operator+=(const v8::Local<v8::String>& s) {
            m_str+=_detail::to_string(s);
            return *this;
        }
    public:
        char operator[](std::size_t idx) {
            return m_str[idx];
        }
        char at(std::size_t idx) {
            return m_str.at(idx);
        }
    public:
        void swap(string& s) {
            std::swap(m_str, s.m_str);
        }
        void swap(std::string& s) {
            std::swap(m_str, s);
        }
        void swap(v8::Local<v8::String>& s) {
            std::string s_tmp=_detail::to_string(s);
            s=v8_str();
            m_str=s_tmp;
        }
    };

    inline string operator+(const string& lhs, const string& rhs) {
        return string(lhs.str()+rhs.str());
    }

    inline string operator+(const std::string& lhs, const string& rhs) {
        return string(lhs+rhs.str());
    }
    inline string operator+(const string& lhs, const std::string& rhs) {
        return string(lhs.str()+rhs);
    }

    inline string operator+(const string& lhs, const char *rhs) {
        return string(lhs.str()+rhs);
    }
    inline string operator+(const char *lhs, const string& rhs) {
        return string(lhs+rhs.str());
    }

    inline string operator+(const string& lhs, char rhs) {
        return string(lhs.str()+rhs);
    }
    inline string operator+(char lhs, const string& rhs) {
        return string(lhs+rhs.str());
    }

    inline bool operator==(const string& lhs, const string& rhs) {
        return lhs.str()==rhs.str();
    }

    inline bool operator==(const std::string& lhs, const string& rhs) {
        return lhs==rhs.str();
    }
    inline bool operator==(const string& lhs, const std::string& rhs) {
        return lhs.str()==rhs;
    }

    inline bool operator==(const string& lhs, const char *rhs) {
        return lhs.str()==rhs;
    }
    inline bool operator==(const char *lhs, const string& rhs) {
        return lhs==rhs.str();
    }

    template<class RhsT> bool operator!=(const string& lhs, RhsT rhs) {
        return !(lhs==rhs);
    }
    template<class LhsT> bool operator!=(LhsT lhs, const string& rhs) {
        return !(lhs==rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const string& s) {
        os<<s.str();
        return os;
    }
    inline std::istream& operator>>(std::istream& is, string& s) {
        std::string str;
        is>>str;
        s=str;
        return is;
    }
} /* nw */

namespace nw {
    namespace _detail {
        inline bool is_numbers(const v8::Local<v8::Value>& val)noexcept {
            return val->IsNumber() || val->IsNumberObject() || val->IsInt32() || val->IsUint32();
        }
        template<class T> bool set_value(const v8::Local<v8::Value>& val, T& target) {
            return false;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, string& target) {
            if(!val->IsString() && !val->IsStringObject())return false;
            target=_detail::to_string(val);
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, std::string& target) {
            if(!val->IsString() && !val->IsStringObject())return false;
            target=_detail::to_string(val);
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, bool& target) {
            if(!val->IsBoolean() && !val->IsBooleanObject())return false;
            target=val->BooleanValue();
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, double& target) {
            if(!is_numbers(val))return false;
            target=val->NumberValue();
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, int& target) {
            if(!is_numbers(val))return false;
            target=val->Int32Value();
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, long long& target) {
            if(!is_numbers(val))return false;
            target=static_cast<long long>(val->NumberValue());
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, unsigned int& target) {
            if(!is_numbers(val))return false;
            target=val->Uint32Value();
            return true;
        }
        template<> bool set_value(const v8::Local<v8::Value>& val, unsigned long long& target) {
            if(!is_numbers(val))return false;
            target=static_cast<unsigned long long>(val->NumberValue());
            return true;
        }

        inline bool get_args_impl(const v8::FunctionCallbackInfo<v8::Value>&, std::size_t)noexcept {
            return true;
        }
        template<class Arg, class... Args> bool get_args_impl(const v8::FunctionCallbackInfo<v8::Value>& args, std::size_t depth, Arg& target, Args&... targets) {
            if(!set_value(args[depth], target))return false;
            return get_args_impl(args, depth+1, targets...);
        }
    } /* _detail */
    template<class... Args> bool get_args(const v8::FunctionCallbackInfo<v8::Value>& args, Args&... targets) {
        if(args.Length()<sizeof...(targets))return false;
        return _detail::get_args_impl(args, 0, targets...);
    }
} /* nw */

namespace nw {
    template<class RetT> void return_nw(const v8::FunctionCallbackInfo<v8::Value>& args, RetT r) {
        args.GetReturnValue().Set(r);
    }
    inline void return_nw(const v8::FunctionCallbackInfo<v8::Value>& args, const nw::string& s) {
        return_nw(args, s.v8_str());
    }
    inline void return_nw(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& s) {
        return_nw(args, nw::string(s));
    }
} /* nw */

#endif /* end of include guard: NODE_GYP_WRAPPER */
