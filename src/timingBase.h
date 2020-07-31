#ifndef __REPLACE_TIMING_BASE__
#define __REPLACE_TIMING_BASE__

#include <memory>
#include <vector>

namespace odb {
  class dbDatabase;
}

 //RCPlace
namespace RCPlace {
  class RCPlace;
}

namespace replace {

class Logger;
class NesterovBase;

class TimingBaseVars {
public:
  TimingBaseVars();
  void reset();
  void addTimingUpdateIter(int overflow);
  void deleteTimingUpdateIter(int overflow);
  void clearTimingUpdateIter();
  size_t getTimingUpdateIterSize() { return timingUpdateIter_.size(); }

private:
  std::vector<int> timingUpdateIter_;

friend class TimingBase;
};

class TimingBase {
  public:
    TimingBase();
    TimingBase(TimingBaseVars tbVars,
        odb::dbDatabase* db, 
        RCPlace::RCPlace* rp, // Added for RCPlace
        std::shared_ptr<NesterovBase> nb,
        std::shared_ptr<Logger> log);
    ~TimingBase();

    // check whether overflow reached the timingIter
    bool isTimingUpdateIter(float overflow);

    // updateNetWeight.
    void updateGNetWeight();

  private:
    TimingBaseVars tbVars_;
    odb::dbDatabase* db_;
    RCPlace::RCPlace* rp_; // Added for RCPlace
    
    std::shared_ptr<NesterovBase> nb_;
    std::shared_ptr<Logger> log_; 

    std::vector<int> timingIterChk_;
    void initTimingIterChk();

    void reset();
};

}

#endif
