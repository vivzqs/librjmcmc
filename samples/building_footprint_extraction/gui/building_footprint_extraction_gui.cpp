#include "core/building_footprint_extraction_parameters_inc.hpp"
#include "gui/wx_parameter_traits.hpp"
template class parameters<wx_parameter_traits>;
typedef parameters<wx_parameter_traits> param;

#include "rjmcmc_building_footprint_extraction_thread.hpp"

#include <wx/app.h>

class building_footprint_extraction_gui : public wxApp
{
public:
	rjmcmc_building_footprint_extraction_frame *m_frame;

private:
	bool OnInit()
	{
		char **my_argv = new char*[argc];
		for (int i=0;i<argc;++i)
		{
			wxString mystr(argv[i]);
			my_argv[i] = new char[mystr.size()+1];
			strcpy(my_argv[i], mystr.To8BitData());
		}
		if(!param::Instance()->parse(argc,my_argv)) return false;
		
		m_frame = new rjmcmc_building_footprint_extraction_frame((wxFrame *)NULL, wxID_ANY, _("RJMCMC building footprint extraction") );
		m_frame->Show();
		return true;
	}
};

IMPLEMENT_APP(building_footprint_extraction_gui);
