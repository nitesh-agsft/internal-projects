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
            redirect_to :action => 'list', :id => @account
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
        redirect_to :action => 'new'
    end  
    
end
