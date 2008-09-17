/*	=======
 *	Task.cc
 *	=======
 */

#include "A-line/Task.hh"

// Standard C++
#include <algorithm>
#include <functional>
#include <queue>

// MoreFunctional
#include "PointerToFunction.hh"

// POSeven
#include "POSeven/Pathnames.hh"
#include "POSeven/Stat.hh"


namespace tool
{
	
	namespace p7 = poseven;
	
	
	using namespace io::path_descent_operators;
	
	
	static std::queue< TaskPtr > gReadyTasks;
	static std::vector< TaskPtr > gFailedTasks;
	
	
	inline void UpdateTaskInputStamp( const TaskPtr& task, time_t stamp )
	{
		task->UpdateInputStamp( stamp );
	}
	
	static void CheckIfTaskIsReady( const TaskPtr& task )
	{
		if ( task.unique() )
		{
			gReadyTasks.push( task );
		}
	}
	
	void Task::UpdateInputStamp( time_t stamp )
	{
		if ( stamp > its_input_stamp )
		{
			its_input_stamp = stamp;
		}
	}
	
	void Task::Run()
	{
		Main();
		
		Complete( its_input_stamp );
	}
	
	void Task::Complete( time_t stamp )
	{
		std::for_each( its_dependents.begin(),
		               its_dependents.end(),
		               std::bind2nd( more::ptr_fun( UpdateTaskInputStamp ),
		                             stamp ) );
		
		std::for_each( its_dependents.begin(),
		               its_dependents.end(),
		               std::ptr_fun( CheckIfTaskIsReady ) );
		
		its_dependents.clear();
	}
	
	
	time_t FileTask::OutputStamp() const
	{
		struct stat output_stat;
		
		const bool output_exists = p7::stat( its_output_path, output_stat );
		
		if ( output_exists )
		{
			return output_stat.st_mtime;
		}
		
		return 0;
	}
	
	bool FileTask::UpToDate()
	{
		return MoreRecent( OutputStamp() );
	}
	
	void FileTask::Main()
	{
		// If the output file exists and it's up to date, we can skip this.
		
		if ( UpToDate() )
		{
			return;
		}
		
		Make();
		
		UpdateInputStamp( p7::stat( its_output_path ).st_mtime );
	}
	
	
	static const char* c_str( const std::string& s )
	{
		return s.c_str();
	}
	
	
	CommandTask::CommandTask( const Command&      command,
			                  const std::string&  output,
			                  const std::string&  diagnostics,
			                  const std::string  *input_begin,
			                  const std::string  *input_end )
	: FileTask( output ),
	  its_command( command ),
	  its_diagnostics_file_path( diagnostics ),
	  its_input_file_paths( input_begin, input_end )
	{
		its_command.reserve( command.size() + 2 + input_end - input_begin );
		
		its_command.push_back( OutputPath().c_str() );
		
		std::transform( its_input_file_paths.begin(),
		                its_input_file_paths.end(),
		                std::back_inserter( its_command ),
		                std::ptr_fun( c_str ));
		
		its_command.push_back( NULL );
	}
	
	
	void AddReadyTask( const TaskPtr& task )
	{
		gReadyTasks.push( task );
	}
	
	bool RunNextTask()
	{
		if ( gReadyTasks.empty() )
		{
			return false;
		}
		
		TaskPtr task = gReadyTasks.front();
		
		gReadyTasks.pop();
		
		task->Run();
		
		return true;
	}
	
}

