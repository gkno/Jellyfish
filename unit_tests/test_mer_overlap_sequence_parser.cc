#include <string>

#include <gtest/gtest.h>
#include <jflib/tmpstream.hpp>
#include <jellyfish/mer_overlap_sequence_parser.hpp>

namespace {
using std::string;
using std::istringstream;
template<typename Iterator>
struct opened_streams {
  Iterator begin_, end_;

  opened_streams(Iterator begin, Iterator end) : begin_(begin), end_(end) { }
  std::unique_ptr<std::istream> next() {
    std::unique_ptr<std::istream> res;
    if(begin_ != end_) {
      res.reset(*begin_);
      ++begin_;
    }
    return res;
  }
};
typedef jellyfish::mer_overlap_sequence_parser<opened_streams<jflib::tmpstream**> > parser_type;


TEST(MerOverlapSequenceParser, OneSmallSequence) {
  static const char* seq = "ATTACCTTGTACCTTCAGAGC";
  jflib::tmpstream* sequence = new jflib::tmpstream;
  *sequence << ">header\n" << seq;
  sequence->seekg(0);
  opened_streams<jflib::tmpstream**> streams(&sequence, &sequence + 1);

  parser_type parser(10, 1, 10, 100, streams);

  parser_type::job j(parser);
  ASSERT_FALSE(j.is_empty());
  EXPECT_EQ(strlen(seq), j->end - j->start);
  EXPECT_STREQ(seq, j->start);
  j.release();

  parser_type::job j2(parser);
  EXPECT_TRUE(j2.is_empty());
}

string generate_sequences(std::ostream& os, int a, int b, int nb, bool fastq = false) {
  static const char bases[4] = {'A', 'C', 'G', 'T' };
  string res;
  for(int i = 0; i < nb; ++i) {
    int len = a + random() % b;
    os << (fastq ? "@" : ">") << "r" << i << " " << len << "\n";
    for(int j = 0; j < len; ++j) {
      char b = bases[random() & 0x3];
      os << b;
      res += b;
      if(random() % 16 == 0)
        os << "\n";
    }
    if(i != nb - 1)
      res += 'N';
    os << "\n";
    if(fastq) {
      os << "+\n";
      for(int j = 0; j < len; ++j) {
        if(random() % 16 == 0)
          os << "\n";
        os << "#";
      }
      os << "\n";
    }
  }
  return res;
}

TEST(MerOverlapSequenceParser, ManySmallSequences) {
  jflib::tmpstream* sequence = new jflib::tmpstream;

  static const int nb_reads = 20;
  static const int mer_len = 10;
  string res = generate_sequences(*sequence, 20, 64, nb_reads);
  sequence->seekg(0);
  opened_streams<jflib::tmpstream**> streams(&sequence, &sequence + 1);

  parser_type parser(mer_len, 1, 10, 100, streams);
  size_t offset = 0;
  while(true) {
    parser_type::job j(parser);
    if(j.is_empty())
      break;
    SCOPED_TRACE(::testing::Message() << offset << ": " << res.substr(offset, j->end - j->start));
    EXPECT_EQ(res.substr(offset, j->end - j->start).c_str(), string(j->start, j->end - j->start));
    offset += j->end - j->start - (mer_len - 1);
  }
  EXPECT_EQ(res.size(), offset + mer_len - 1);
}

TEST(MerOverlapSequenceParser, BigSequences) {
  jflib::tmpstream* tmps[2];
  tmps[0] = new jflib::tmpstream;
  string res0 = generate_sequences(*tmps[0], 200, 100, 3);
  tmps[0]->seekg(0);
  tmps[1] = new jflib::tmpstream;
  string res1 = generate_sequences(*tmps[1], 200, 100, 3);
  tmps[1]->seekg(0);
  opened_streams<jflib::tmpstream**> streams(tmps, tmps + 2);

  static const int mer_len = 10;
  parser_type parser(mer_len, 1, 10, 100, streams);

  size_t offset = 0;
  while(offset < res0.size() - mer_len + 1) {
    parser_type::job j(parser);
    ASSERT_FALSE(j.is_empty());
    SCOPED_TRACE(::testing::Message() << offset << ": " << res0.substr(offset, j->end - j->start));
    EXPECT_EQ(res0.substr(offset, j->end - j->start).c_str(), string(j->start, j->end - j->start));
    offset += j->end - j->start - (mer_len - 1);
  }
  EXPECT_EQ(res0.size(), offset + mer_len - 1);

  offset = 0;
  while(offset < res1.size() - mer_len + 1) {
    parser_type::job j(parser);
    ASSERT_FALSE(j.is_empty());
    SCOPED_TRACE(::testing::Message() << offset << ": " << res1.substr(offset, j->end - j->start));
    EXPECT_EQ(res1.substr(offset, j->end - j->start).c_str(), string(j->start, j->end - j->start));
    offset += j->end - j->start - (mer_len - 1);
  }
  EXPECT_EQ(res1.size(), offset + mer_len - 1);

  parser_type::job j2(parser);
  EXPECT_TRUE(j2.is_empty());
}

TEST(MerOverlapSequenceParser, Fastq) {
  jflib::tmpstream* sequence = new jflib::tmpstream;
  static const int nb_reads = 100;
  static const int mer_len = 20;
  string res = generate_sequences(*sequence, 10, 50, nb_reads, true);
  sequence->seekg(0);
  opened_streams<jflib::tmpstream**> streams(&sequence, &sequence + 1);
  parser_type parser(mer_len, 1, 10, 100, streams);

  size_t offset = 0;
  while(true) {
    parser_type::job j(parser);
    if(j.is_empty())
      break;
    //    SCOPED_TRACE(::testing::Message() << offset << ": " << res.substr(offset, j->end - j->start));
    EXPECT_EQ(res.substr(offset, j->end - j->start).c_str(), string(j->start, j->end - j->start));
    offset += j->end - j->start - (mer_len - 1);
  }
  EXPECT_EQ(res.size(), offset + mer_len - 1);
}
} // namespace {
