// this is -*- c++ -*-
#ifndef OKSCONFLIBS_OKSCONFLIBSOBJECT_H_
#define OKSCONFLIBS_OKSCONFLIBSOBJECT_H_

#include <string>
#include <vector>

#include "oks/kernel.hpp"
#include "oks/object.hpp"

#include "conffwk/ConfigObjectImpl.hpp"

namespace dunedaq {
namespace oksconflibs {

class ConfigurationImpl;
class OksConfiguration;

  class OksConfigObject :  public conffwk::ConfigObjectImpl {

  friend class ConfigurationImpl;
  friend class OksConfiguration;

  public:

    OksConfigObject(oks::OksObject *obj, conffwk::ConfigurationImpl * impl) noexcept;
    virtual ~OksConfigObject() noexcept;


  public:

    virtual const std::string contained_in() const;

    virtual void get(const std::string& name, bool&           value);
    virtual void get(const std::string& name, uint8_t&        value);
    virtual void get(const std::string& name, int8_t&         value);
    virtual void get(const std::string& name, uint16_t&       value);
    virtual void get(const std::string& name, int16_t&        value);
    virtual void get(const std::string& name, uint32_t&       value);
    virtual void get(const std::string& name, int32_t&        value);
    virtual void get(const std::string& name, uint64_t&       value);
    virtual void get(const std::string& name, int64_t&        value);
    virtual void get(const std::string& name, float&          value);
    virtual void get(const std::string& name, double&         value);
    virtual void get(const std::string& name, std::string&    value);
    virtual void get(const std::string& name, conffwk::ConfigObject&   value);

    virtual void get(const std::string& name, std::vector<bool>&           value);
    virtual void get(const std::string& name, std::vector<uint8_t>&        value);
    virtual void get(const std::string& name, std::vector<int8_t>&         value);
    virtual void get(const std::string& name, std::vector<uint16_t>&       value);
    virtual void get(const std::string& name, std::vector<int16_t>&        value);
    virtual void get(const std::string& name, std::vector<uint32_t>&       value);
    virtual void get(const std::string& name, std::vector<int32_t>&        value);
    virtual void get(const std::string& name, std::vector<uint64_t>&       value);
    virtual void get(const std::string& name, std::vector<int64_t>&        value);
    virtual void get(const std::string& name, std::vector<float>&          value);
    virtual void get(const std::string& name, std::vector<double>&         value);
    virtual void get(const std::string& name, std::vector<std::string>&    value);
    virtual void get(const std::string& name, std::vector<conffwk::ConfigObject>&   value);

    virtual bool rel(const std::string& name, std::vector<conffwk::ConfigObject>& value);
    virtual void referenced_by(std::vector<conffwk::ConfigObject>& value, const std::string& association, bool check_composite_only, unsigned long rlevel, const std::vector<std::string> * rclasses) const;


    virtual void set(const std::string& name, bool                value);
    virtual void set(const std::string& name, uint8_t             value);
    virtual void set(const std::string& name, int8_t              value);
    virtual void set(const std::string& name, uint16_t            value);
    virtual void set(const std::string& name, int16_t             value);
    virtual void set(const std::string& name, uint32_t            value);
    virtual void set(const std::string& name, int32_t             value);
    virtual void set(const std::string& name, uint64_t            value);
    virtual void set(const std::string& name, int64_t             value);
    virtual void set(const std::string& name, float               value);
    virtual void set(const std::string& name, double              value);
    virtual void set(const std::string& name, const std::string&  value);

    virtual void set_enum(const std::string& attribute, const std::string& value);
    virtual void set_date(const std::string& attribute, const std::string& value);
    virtual void set_time(const std::string& attribute, const std::string& value);

    virtual void set_class(const std::string& attribute, const std::string& value);

    virtual void set(const std::string& name, const std::vector<bool>&           value);
    virtual void set(const std::string& name, const std::vector<uint8_t>&        value);
    virtual void set(const std::string& name, const std::vector<int8_t>&         value);
    virtual void set(const std::string& name, const std::vector<uint16_t>&       value);
    virtual void set(const std::string& name, const std::vector<int16_t>&        value);
    virtual void set(const std::string& name, const std::vector<uint32_t>&       value);
    virtual void set(const std::string& name, const std::vector<int32_t>&        value);
    virtual void set(const std::string& name, const std::vector<uint64_t>&       value);
    virtual void set(const std::string& name, const std::vector<int64_t>&        value);
    virtual void set(const std::string& name, const std::vector<float>&          value);
    virtual void set(const std::string& name, const std::vector<double>&         value);
    virtual void set(const std::string& name, const std::vector<std::string>&    value);

    virtual void set_enum(const std::string& attribute, const std::vector<std::string>& value);
    virtual void set_date(const std::string& attribute, const std::vector<std::string>& value);
    virtual void set_time(const std::string& attribute, const std::vector<std::string>& value);

    virtual void set_class(const std::string& attribute, const std::vector<std::string>& value);

    virtual void set(const std::string& name, const conffwk::ConfigObject*                     value, bool skip_non_null_check);
    virtual void set(const std::string& name, const std::vector<const conffwk::ConfigObject*>& value, bool skip_non_null_check);

    virtual void move(const std::string& at);
    virtual void rename(const std::string& new_id);

    virtual void reset();

  public:

      // required by JNI

    oks::OksData::Type get_type(const std::string& attribute) const;


    // helper functions

  private:

      // extract values out of OKS database

    template<class T> void get_value(const std::string& name, T& value);
    template<class T> void get_vector(const std::string& name, std::vector<T>& value);


      // set values in OKS database

    void set_attr_value(const std::string& name, oks::OksData& value);
    void set_rel_value(const std::string& name, oks::OksData& value, bool skip_non_null_check);

    template<class T> void set_value(const std::string& name, const T& value);
    template<class T> void set_vector(const std::string& name, const std::vector<T>& value);


      // checkout file, if is needed for update

//    void test_checkout_needs();

  public:
    // required by template method insert_object
    void set(oks::OksObject *obj)
      {
        m_obj = obj;
      }

    // representation

  private:

    oks::OksObject *m_obj;
};

} // namespace oksconflibs
} // namespace dunedaq

#endif // OKSCONFLIBS_OKSCONFLIBSOBJECT_H_
