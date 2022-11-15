const InputName = (props) => {
  const { title, type, name, value, onChange, pre } = props;

  return (
    <div className='input-container'>
      <label className='input-name' htmlFor={title}>
        {title.toUpperCase()}
      </label>
      <input
        type={type ?? title}
        name={name ?? title}
        value={value}
        onChange={onChange}
        placeholder={pre}
        className='input-inputs'
      />
    </div>
  );
};

export default InputName;
