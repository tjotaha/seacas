/*
 * Copyright(C) 1999-, 20242024,  National Technology & Engineering Solutions
 * of Sandia, LLC (NTESS).  Under the terms of Contract DE-NA0003525 with
 * NTESS, the U.S. Government retains certain rights in this software.
 *
 * See packages/seacas/LICENSE for details
 */
#pragma once

#include <string>
#include <vector>

namespace Excn {

  class SystemInterface;
  class ExodusFile
  {
  public:
    explicit ExodusFile(int processor);
    ~ExodusFile();
    ExodusFile(const ExodusFile &)           = delete;
    ExodusFile operator=(const ExodusFile &) = delete;

    static void initialize(const SystemInterface &si, int start_part, int part_count, int cycle,
                           bool joining_subcycle);
    static void create_output(const SystemInterface &si, int cycle);
    static void close_all();

    static int set_active_change_set(int cs);
    static int get_active_change_set() { return activeChangeSet_; }
    static int get_change_set_count() { return changeSetCount_; }

    static int output();
    static int io_word_size() { return ioWordSize_; }
    operator int() const;
    static int  max_name_length() { return maximumNameLength_; }
    static void handle_temporary_files(bool delete_them);
    static void unlink_input_files();

  private:
    static void set_change_set_count(int exoid);

    int                             myProcessor_;
    static std::vector<std::string> filenames_;
    static std::vector<int>         fileids_;
    static std::string              outputFilename_;
    static int                      processorCount_;
    static int                      partCount_;
    static int                      startPart_;
    static int                      outputId_;
    static int                      ioWordSize_;
    static int                      cpuWordSize_;
    static int                      maximumNameLength_;
    static int                      mode64bit_;
    static int                      changeSetCount_;
    static int                      activeChangeSet_;
    static int                      activeOutputChangeSet_;
    static bool                     keepOpen_;
    static bool                     verifyValidFile_;
    static bool                     onlySelectedChangeSet_;
  };
} // namespace Excn
