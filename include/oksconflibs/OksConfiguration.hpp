// this is -*- c++ -*-
#ifndef OKSCONFLIBS_OKSCONFLIBSURATION_H_
#define OKSCONFLIBS_OKSCONFLIBSURATION_H_

//
// $Id$
//

#include <string>
#include <list>
#include <set>
#include <thread>

#include "conffwk/ConfigurationImpl.hpp"

namespace dunedaq {
namespace oks {
  // forward declarations for OKS classes
  class OksKernel;
  class OksObject;
  class OksClass;
  class OksFile;
}

namespace oksconflibs {

  // forward declaration 
class OksConfigObject;
struct OksConfigurationCheckDB;


class OksConfiguration : public conffwk::ConfigurationImpl {

  friend class OksConfigObject;
  friend struct OksConfigurationCheckDB;
  friend class ResubscribeGuard;

  public:

    OksConfiguration() noexcept : m_kernel (nullptr), m_fn (0),
                                  m_oks_kernel_no_repo(false),
                                  m_check_db_obj (nullptr),
                                  m_check_db_thread (nullptr),
                                  m_repo_error_count(0) {
        init_env();
    }

    ~OksConfiguration() override {close_db();}

    typedef std::map< std::string , std::set<std::string> > SMap;

    bool test_object(const std::string& class_name, const std::string& name, unsigned long rlevel, const std::vector<std::string> * rclasses) override;
    void get(const std::string& class_name, const std::string& name, conffwk::ConfigObject& object, unsigned long rlevel, const std::vector<std::string> * rclasses) override;
    void get(const std::string& class_name, std::vector<conffwk::ConfigObject>& objects, const std::string& query, unsigned long rlevel, const std::vector<std::string> * rclasses) override;
    void get(const conffwk::ConfigObject& obj_from, const std::string& query, std::vector<conffwk::ConfigObject>& objects, unsigned long rlevel, const std::vector<std::string> * rclasses) override;
    conffwk::class_t * get(const std::string& class_name, bool direct_only) override;
    void get_superclasses(conffwk::fmap<conffwk::fset>& schema) override;

    void create(const std::string& at, const std::string& class_name, const std::string& id, conffwk::ConfigObject& object) override;
    void create(const conffwk::ConfigObject& at, const std::string& class_name, const std::string& id, conffwk::ConfigObject& object) override;
    void destroy(conffwk::ConfigObject& object) override;

    void open_db(const std::string& db_name) override;
  void close_db() override { close_database(true); };
    bool loaded() const noexcept override { return (m_kernel != 0); }
    void create(const std::string& db_name, const std::list<std::string>& includes) override;
    bool is_writable(const std::string& db_name) override;
    void add_include(const std::string& db_name, const std::string& include) override;
    void remove_include(const std::string& db_name, const std::string& include) override;
    void get_includes(const std::string& db_name, std::list<std::string>& includes) const override;
    std::vector<std::string> get_schema() const override;
    void get_updated_dbs(std::list<std::string>& dbs) const override;
    void set_commit_credentials(const std::string& user, const std::string& password) override;
    void commit(const std::string& why) override;
    void abort() override;
    void prefetch_all_data() override {} // nothing to do with OKS data already in-memory
    std::vector<dunedaq::conffwk::Version> get_changes() override;
    std::vector<dunedaq::conffwk::Version> get_versions(const std::string& since, const std::string& until, dunedaq::conffwk::Version::QueryType type, bool skip_irrelevant) override;

    void subscribe(const std::set<std::string>& class_names, const SMap& objs, ConfigurationImpl::notify cb, ConfigurationImpl::pre_notify pre_cb) override;
    void unsubscribe() override;

    void print_profiling_info() noexcept override;


  protected:

    void create(oks::OksFile * at, const std::string& class_name, const std::string& id, conffwk::ConfigObject& object);

  private:

    virtual void check_db();

    void close_database(bool unsubscribe);


  public:

    [[nodiscard]] const oks::OksKernel& get_oks_kernel() const { return *m_kernel; }  // required by Java oksconflibs


  protected:

    oks::OksKernel * m_kernel;
    conffwk::ConfigurationImpl::notify m_fn;
    conffwk::ConfigurationImpl::pre_notify m_pre_fn;
    std::set<std::string> m_class_names;
    SMap m_objects;
    bool m_oks_kernel_silence;
    bool m_oks_kernel_no_repo;

      // read oks::OksKernel parameters from environment (silence mode)
    void init_env();


    OksConfigObject * new_object(oks::OksObject * obj) noexcept;



      // keep information about changed objects

    std::list<oks::OksObject *> m_created;
    std::set<oks::OksObject *> m_modified;
    std::map<std::string, std::set<std::string> > m_removed;

    void subscribe();

    static void create_notify(oks::OksObject *, void *) noexcept;
    static void change_notify(oks::OksObject *, void *) noexcept;
    static void delete_notify(oks::OksObject *, void *) noexcept;

    OksConfigurationCheckDB * m_check_db_obj;
    std::thread * m_check_db_thread;

    std::string m_user;
    std::string m_password;


      // keep information about created files
    std::set<oks::OksFile *> m_created_files;


      //
    unsigned int m_repo_error_count;

};

} // namespace oksconflibs
} // namespace dunedaq

#endif // OKSCONFLIBS_OKSCONFLIBSURATION_H_
