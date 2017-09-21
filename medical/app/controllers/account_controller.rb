class AccountController < ApplicationController
    layout 'standard' 
    
    def list
        @account = Account.all
       
    end
   
    def show
        @account = Account.find(params[:id])
       
    end
   
    def new
       @account = Account.new
    end
   
    def create
        @account = Account.new(accountparams)
        if @account.save
            redirect_to :action => 'list'
        else
            render :action => 'new'
        end
        
    end
    
    def accountparams
        params.require(:accounts).permit(:account_no, :lastname, :firstname, :middlename, :gender, :birthdate, :headofhouse) 
    end
   
    def edit
        @account = Account.find(params[:id])
    end
   
    def update
        @account = Account.find(params[:id])
        if @account.update_attributes(accountparamsu)
            redirect_to :action => 'list'
        else
            render :action => 'edit'
        end
    end
    def accountparamsu
        params.require(:account).permit(:account_no, :lastname, :firstname, :middlename, :gender, :birthdate, :headofhouse) 
    end
   
    def delete
        @account = Account.find(params[:id]).destroy
        redirect_to :action => 'list'
       
    end
    def autoassign
        puts "auto-assign" 
        
        begin
            #@rndno = '%05d' % rand(5** 5)
            @rndno = rand(99999).to_s.center(5, rand(9).to_s).to_i
            @gotval = Account.find_by_account_no(@rndno)
        end while @gotval != nil
            
        puts @rndno
        puts @gotval
        redirect_to :action => 'new', :autoaccn => @rndno
    end  
    
end
