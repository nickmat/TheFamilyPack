#include "wx/wxprec.h"
#include "wx/cppunit.h"

// define wxHAVE_U_ESCAPE if the compiler supports \uxxxx character constants
#if (defined(__VISUALC__) && (__VISUALC__ >= 1300)) || \
    (defined(__GNUC__) && (__GNUC__ >= 3))
    #define wxHAVE_U_ESCAPE
#endif

// thrown when assert fails in debug build
class TestAssertFailure
{
public:
    TestAssertFailure(const wxString& file,
                      int line,
                      const wxString& func,
                      const wxString& cond,
                      const wxString& msg)
        : m_file(file),
          m_line(line),
          m_func(func),
          m_cond(cond),
          m_msg(msg)
    {
    }

    const wxString m_file;
    const int m_line;
    const wxString m_func;
    const wxString m_cond;
    const wxString m_msg;

    wxDECLARE_NO_ASSIGN_CLASS(TestAssertFailure);
};

// macro to use for the functions which are supposed to fail an assertion
#if wxDEBUG_LEVEL
    // some old cppunit versions don't define CPPUNIT_ASSERT_THROW so roll our
    // own
    #define WX_ASSERT_FAILS_WITH_ASSERT(cond) \
        { \
            bool throwsAssert = false; \
            try { cond ; } \
            catch ( const TestAssertFailure& ) { throwsAssert = true; } \
            if ( !throwsAssert ) \
                CPPUNIT_FAIL("expected assertion not generated"); \
        }
#else
    // there are no assertions in this build so just check that it fails
    #define WX_ASSERT_FAILS_WITH_ASSERT(cond) CPPUNIT_ASSERT(!(cond))
#endif

// these functions can be used to hook into wxApp event processing and are
// currently used by the events propagation test
class WXDLLIMPEXP_FWD_BASE wxEvent;

typedef int (*FilterEventFunc)(wxEvent&);
typedef bool (*ProcessEventFunc)(wxEvent&);

extern void SetFilterEventFunc(FilterEventFunc func);
extern void SetProcessEventFunc(ProcessEventFunc func);
