import java.util.Date; 
public class kj {
	private Integer id; 
	private Integer tkid; 
	private String answer; 
	private String name; 
	private String createtime; 

	public kj (){

	}

	public void setId(Integer id){
		this.id=id;
	}
	public Integer getId(){
		return id;
	}

	public void setTkid(Integer tkid){
		this.tkid=tkid;
	}
	public Integer getTkid(){
		return tkid;
	}

	public void setAnswer(String answer){
		this.answer=answer;
	}
	public String getAnswer(){
		return answer;
	}

	public void setName(String name){
		this.name=name;
	}
	public String getName(){
		return name;
	}

	public void setCreatetime(String createtime){
		this.createtime=createtime;
	}
	public String getCreatetime(){
		return createtime;
	}

	@Override
	public String toString(){
		return " kj [id=" + id+ " , tkid=" + tkid+ " , answer=" + answer+ " , name=" + name+ " , createtime=" + createtime+"]";
	}

}

