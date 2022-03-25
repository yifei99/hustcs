import java.util.Date; 
public class tk {
	private Integer id; 
	private String title; 
	private String type; 
	private String other; 
	private String answer; 
	private double score; 

	public tk (){

	}

	public void setId(Integer id){
		this.id=id;
	}
	public Integer getId(){
		return id;
	}

	public void setTitle(String title){
		this.title=title;
	}
	public String getTitle(){
		return title;
	}

	public void setType(String type){
		this.type=type;
	}
	public String getType(){
		return type;
	}

	public void setOther(String other){
		this.other=other;
	}
	public String getOther(){
		return other;
	}

	public void setAnswer(String answer){
		this.answer=answer;
	}
	public String getAnswer(){
		return answer;
	}

	public void setScore(double score){
		this.score=score;
	}
	public double getScore(){
		return score;
	}

	@Override
	public String toString(){
		return " tk [id=" + id+ " , title=" + title+ " , type=" + type+ " , other=" + other+ " , answer=" + answer+ " , score=" + score+"]";
	}

}

