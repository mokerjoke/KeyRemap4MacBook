// This header intentionally has no include guards.

class language {
public:
  class value_type {
  public:
    enum type {
      none,
      bcp47,
      inputsourceid_equal,
      inputsourceid_prefix,
      inputmodeid_equal,
      inputmodeid_prefix,
    };

    static type get_type_from_string(const std::string& string) {
      if (string == "bcp47")                { return type::bcp47; }
      if (string == "inputsourceid_equal")  { return type::inputsourceid_equal; }
      if (string == "inputsourceid_prefix") { return type::inputsourceid_prefix; }
      if (string == "inputmodeid_equal")    { return type::inputmodeid_equal; }
      if (string == "inputmodeid_prefix")   { return type::inputmodeid_prefix; }
      return type::none;
    }
  };

  const boost::optional<std::string>& get_name(void) const { return name_; }
  void set_name(const std::string& v) { name_ = v; }

  const boost::optional<std::string>& get_detail(void) const { return detail_; }
  void set_detail(const std::string& v) { detail_ = v; }

  const boost::optional<std::string>& get_value(void) const { return value_; }
  void set_value(const std::string& v) { value_ = v; }

  value_type::type get_value_type(void) const { return value_type_; }
  void set_value_type(value_type::type v) { value_type_ = v; }

  bool is_rules_matched(const std::string& bcp47,
                        const std::string& inputsourceid,
                        const std::string& inputmodeid) const;

private:
  boost::optional<std::string> name_;
  boost::optional<std::string> detail_;
  boost::optional<std::string> value_;
  value_type::type value_type_;
};

class language_loader {
public:
  language_loader(const xml_compiler& xml_compiler,
                  symbol_map& symbol_map,
                  remapclasses_initialize_vector& remapclasses_initialize_vector,
                  std::tr1::unordered_map<uint32_t, std::string>& identifier_map,
                  std::tr1::unordered_map<uint32_t, std::tr1::shared_ptr<language> >& vk_change_inputsource_map,
                  std::vector<std::tr1::shared_ptr<language> >& language_vector) :
    xml_compiler_(xml_compiler),
    symbol_map_(symbol_map),
    remapclasses_initialize_vector_(remapclasses_initialize_vector),
    identifier_map_(identifier_map),
    vk_change_inputsource_map_(vk_change_inputsource_map),
    language_vector_(language_vector)
  {}
  ~language_loader(void);

  void traverse(const extracted_ptree& pt) const;

private:
  class definition_type {
  public:
    enum type {
      none,
      vkchangeinputsourcedef,
      languagedef,
    };
  };

  const xml_compiler& xml_compiler_;
  symbol_map& symbol_map_;
  remapclasses_initialize_vector& remapclasses_initialize_vector_;
  std::tr1::unordered_map<uint32_t, std::string>& identifier_map_;

  std::tr1::unordered_map<uint32_t, std::tr1::shared_ptr<language> >& vk_change_inputsource_map_;
  std::vector<std::tr1::shared_ptr<language> >& language_vector_;
};
