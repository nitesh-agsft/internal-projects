class PlanlistController < ApplicationController
    layout 'standard'
    
    def update
        @plupdate = Planlist.find(params[:id])
        if @plupdate.update_attributes(updateattributes)
            redirect_to :action => 'list'
        else
            render_to :action => 'edit'
        end        
    end
    
    def edit
        @pledit = Planlist.find(params[:id])        
    end
    
    def create
        @createplan = Planlist.new(createparams)
        if @createplan.save
            redirect_to :action => 'list'
        else
            puts "sorry error"
        end
    end
    
    def createparams
        params.require(:planlists).permit(:planid, :planname)
    end
    
    def delete
        Planlist.find(params[:id]).destroy
        redirect_to :action => "list"
    end
    
    def new
        @plnew = Planlist.new
    end
    
    def list
        @pllist = Planlist.all        
    end
    
end
